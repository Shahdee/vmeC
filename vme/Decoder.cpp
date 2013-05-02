#include "StdAfx.h"
#include "Decoder.h"
#include "DicomDictionary.h"
#include <string>
#include <sstream>

CDecoder::CDecoder(void)
{
	m_littleEndian = true;
	m_compressedImage = false;

	m_signedImage = false;
    m_dicomFileReadSuccess = false;
    m_readingDataElements = true;
    m_oddLocations = false;
	m_delimiter = false; // ?
	m_dicomDir = false;
	m_location = 0; // pointer location in file
	m_position = -1;
	m_bitsAllocated = 0;
	m_width = 1;
	m_height = 1;
	m_offset = 1;
	m_nImages = 1;
	m_samplesPerPixel = 1;
	m_photoInterpretation = "";
	m_unit = "mm";
	m_windowCentre = 1;
	m_windowWidth = 1;

	m_inSequence = false;
	m_itemDelimiter = false;
	m_sequenceDelimiter = false ;


}


CDecoder::~CDecoder(void)
{

}

string CDecoder::GetString(int size){
	
	char* buff = new char[size];
	m_dicomFile.read(buff, size);
	m_location+=size;
	return buff;

}

unsigned char CDecoder::ReadByte(){
	m_location++;
	return m_dicomFile.get();
}

unsigned short CDecoder::ReadUShort(){
	unsigned char b0 = ReadByte();
	unsigned char b1 = ReadByte();

	if(m_littleEndian){
		return (unsigned short)((b1 << 8) + b0);
	}
	else{
		return (unsigned short)((b0 << 8) + b1);
	}

	return 0;
}

unsigned int CDecoder::ReadInt(){
	
	unsigned char b0 = ReadByte();
	unsigned char b1 = ReadByte();
	unsigned char b2 = ReadByte();
	unsigned char b3 = ReadByte();

	if(m_littleEndian){
		return ((b3<<24)+(b2<<16)+(b1<<8)+b0);
	}
	else{
		return ((b0<<24)+(b1<<16)+(b2<<8)+b3);
	}
}

unsigned int CDecoder::ReadTag(){

	unsigned short b0 = ReadUShort();
	unsigned short b1 = ReadUShort();

	return (unsigned int)((b0 << 16) + b1);
}

int CDecoder::ReadElementLength(){
	
	unsigned char b0 = ReadByte();
	unsigned char b1 = ReadByte();
	unsigned char b2 = ReadByte();
	unsigned char b3 = ReadByte();

	m_vr = (b0 << 8) + b1 ;

	switch(m_vr)
	{
		case OB:
		case OW:
		//case OF:
		case SQ:
		case UT: 
		case UN:{	  
				 if(b2 ==0 && b3 ==0){
					return ReadInt(); // 4 bytes
				 }
				// implicit VR Data Element
				else{

					m_vr = m_IMPLICIT_VR;

					if (m_littleEndian){
                        return ((b3 << 24) + (b2 << 16) + (b1 << 8) + b0);
					}
                    else{
                        return ((b0 << 24) + (b1 << 16) + (b2 << 8) + b3);
					}
			   }
		}
		case AE:
		case AS:
		case AT:
		case CS:
		case DA:
		case DS:
		case DT:
		case FD:
		case FL:
		case IS:
		case LO:
		case LT:
		case PN:
		case SH:
		case SL:
		case SS:
		case ST:
		case TM:
		case UI:
		case UL:
		case US:
		case QQ:{
			if (m_littleEndian){
				return ((b3 << 8) + b2);
			}
            else{
				return ((b2 << 8) + b3);
					}
			}
		default:{

			m_vr = m_IMPLICIT_VR;

			if (m_littleEndian){
				return ((b3 << 24) + (b2 << 16) + (b1 << 8) + b0);
			}
            else{
				return ((b0 << 24) + (b1 << 16) + (b2 << 8) + b3);
			}
		}
	}
}

void CDecoder::SkipBytes(const int& length){

	m_dicomFile.seekg(length, ios::cur); 	
	m_location += length;
}


void CDecoder::TrySkipSequence(){

	// now it is the only one real case
	if(m_elementLength == -1){

		m_sequenceDelimiter = true;
	}
	else{

		if(m_elementLength == 0 ){  // sequence with no items

			m_sequenceDelimiter = false;
			m_inSequence = false;
			m_itemDelimiter = false;

			return;
		}
		else{

			m_sequenceDelimiter = false;
			m_inSequence = false;
			m_itemDelimiter = false;

			SkipBytes(m_elementLength);
			m_elementLength = 0;
		}
	}
	return;
}

/*
* Read item nested in Sequence of Items in Data Element
*/
void CDecoder::ReadItem(){
	

	unsigned int tag = ReadTag(); // 4
	int length = ReadInt(); // ReadInt() instead of ReadElementLength because we are in sequence

	// string conversion 
	//stringstream ss;
	//ss << tag;
	//string const textTag = ss.str();

	switch(tag){
		
		case ITEM:{

			if(length==-1){

				//ReadDataSet();

				unsigned int itemtag = ReadTag(); // 4
				int itemLength = ReadInt();  //4  ReadInt() instead of ReadElementLength because we are in sequence
				
				if(itemtag==ITEM_DELIMITATION && itemLength==0){
					m_itemDelimiter = true;
					return;
				}
			}
			else{
				//ReadDataSet();
				SkipBytes(length);
			}

			break;
		}

		case SEQUENCE_DELIMITATION:{
				
			if(length==0){
				m_sequenceDelimiter = false;
				m_inSequence = false; 
				m_itemDelimiter = false;  // no reason
			}
			break;
		}

		// strange case
		default:{
			m_sequenceDelimiter = false;
			m_inSequence = false;
			m_itemDelimiter = false;
			return;
		}
	}
}


/*
If we have Data Element with VR = SQ
*/
void CDecoder::ReadSequence(){
	
	while(m_inSequence){
		ReadItem();
	}
}

char* CDecoder::GetString(){

	//vector<char> buf(m_elementLength);

	char *buf = new char[m_elementLength+1];
	m_dicomFile.read(buf, m_elementLength);

	buf[m_elementLength]=0;
	m_location+=m_elementLength;
	
	return buf;
}

void CDecoder::AddInfo(const unsigned int& tag, string& value){
	
	unsigned int valueRepresentation = 0;

	if(m_vr == m_IMPLICIT_VR){

		//map<unsigned int, string>::const_iterator it = dictionary.find(tag);
		string iodsAttText =  dictionary.find(tag)->second;
		string vr = iodsAttText.substr(0, 2);
		valueRepresentation = atoi(&(vr[0]));
	}
	else{
		valueRepresentation = m_vr;
	}

	switch(valueRepresentation){


		case LO:
		case CS:
		case PN:
		case DA:
		case DS:
		case UI:{

 			value.assign(GetString()); 
			break;
		}

		//special VR
		case OB:
		case OW:
		//case OF:
		case SQ:
		case UT: 
		case UN:
		//--e

		case AE:
		case AS:
		case AT:

		case DT:
		case FD:
		case FL:
		case IS:
		case LT:
		case SH:
		case SL:
		case SS:
		case ST:
		case TM:
		case UL:{
			
			// dummy
			m_dicomFile.seekg(m_elementLength, ios::cur);
			m_location+=m_elementLength;
			break;
			// --e
				
		}


		case US:{
			// in ReadFile(QString) method
		}

		case QQ:{
			
			// dummy
			m_dicomFile.seekg(m_elementLength, ios::cur);
			m_location+=m_elementLength;
			break;
			// --e
		}
	}
}

// it is assumed that DICOM default transfer syntax is implicit VR, little endian
void CDecoder::ReadFile(QString path){

	string dummyString; // dummy

	long offset  = CDecoder::FIRST_OFFSET;

	m_dicomFile.open(path.toStdString(), ios::binary);

	if(m_dicomFile.is_open()){
	
		m_dicomFile.seekg(offset, ios::beg); 
		
		m_location += offset;

		string dicom="1234";
		GetString(4).copy(&(dicom[0]), 4, 0);

		if(CDecoder::DICM.compare(0, 4, dicom)!=0){

			return;
		}
		else{
			
			while(m_readingDataElements){
				
				unsigned int tag = ReadTag();
				m_tag = tag;

				m_elementLength = ReadElementLength();

				// I think sometimes it could fail check, for example m_elementLength could be even number of bytes for vr = SQ
				if (m_elementLength == -1 && tag != PIXEL_DATA){
                    m_inSequence = true;
					TrySkipSequence();
                }

				/*
				if ((m_location & 1) != 0){
                    m_oddLocations = true;
				}
				*/

                if (m_inSequence){
                    //AddInfo(tag, dummyString);  
					ReadSequence();
					m_elementLength = 0; // reset
                    continue;
                }
				
				switch (m_tag)
				{

				case TRANSFER_SYNTAX_UID:{
					
					AddInfo(tag, dummyString);
					if(dummyString.compare("1.2.4")==0 || dummyString.compare("1.2.5")==0)
				    {
                            m_compressedImage = true;
                    }

                    if (dummyString.compare("1.2.840.10008.1.2.2")== 0)
                    {
                            m_littleEndian = false;
                    }
                    break;
				}

					case PATIENTS_NAME:{

						AddInfo(tag, m_patientsName);
						break;
					}
					case PATIENT_ID:{

						AddInfo(tag, m_patientID);
						break;				
					}
					case PATIENTS_BIRTHDATE:{

						AddInfo(tag, m_patientsBirthdate);
						break;						
					}
                    case PATIENTS_SEX:{

						AddInfo(tag, m_patientsSex);
						break;

					}
                    
					case BITS_ALLOCATED:{
						
						m_bitsAllocated = ReadUShort();
						break;

					}

					case ROWS:{

						//AddInfo(tag, dummyString);
						//m_width = atoi(dummyString.c_str());

						m_width = ReadUShort();
						break;
					}

					case COLUMNS:{

						//AddInfo(tag, dummyString);
						//m_height = atoi(dummyString.c_str());

						m_height = ReadUShort();
						break;
							 
					}

					case IMAGE_POSITION:{
						
						AddInfo(tag, m_imagePosition);
						break;
					}

					case IMAGE_ORIENTATION:{ // retired (PS 3.6)
							
						AddInfo(tag, m_imageOrientation);
						break;
					}

					case IMAGE_ORIENTATION_PATIENT:{ 
							
						AddInfo(tag, m_imageOrientationPatient);
						break;
					}

					case SLICE_THICKNESS:{
						
						AddInfo(tag, m_sliceThikness);
						//
						break;
					}

					case SLICE_SPACING:{

						AddInfo(tag, m_sliceSpasing);	
						//
						break;
					}

					case PIXEL_REPRESENTATION:{
							
						m_pixelRepresentation = ReadUShort();
						break;
					}

					case SAMPLES_PER_PIXEL:{
						
						AddInfo(tag, dummyString);
						m_samplesPerPixel = atoi(dummyString.c_str());
						break;
					}

					case RESCALE_SLOPE:{
							
						AddInfo(tag, dummyString);
						m_rescaleSlope = atof(dummyString.c_str());
						break;
					}
					case RESCALE_INTERCEPT:{
					
						AddInfo(tag, dummyString);
						m_rescaleIntercept = atof(dummyString.c_str());
						break;
					}

					case WINDOW_CENTER:{
						
						AddInfo(tag, dummyString);
						m_windowCentre = atof(dummyString.c_str());
						break;
					}

					case WINDOW_WIDTH:{
					
						AddInfo(tag, dummyString);
						m_windowWidth = atof(dummyString.c_str());
						break;
					}

					case PIXEL_DATA:{

						if(!m_compressedImage){
							

						}
						else{
						
						}
					}

					default:{
						
						AddInfo(tag, dummyString);
						break;
					}
				}
			}

		}
	}
}


const string CDecoder::DICM = "DICM";

double CDecoder::m_pixelDepth = 1.0;
double CDecoder::m_pixelWidth = 1.0;
double CDecoder::m_pixelHeight = 1.0f;

const map<unsigned int, string> CDecoder::dictionary = CDicomDictionary::InitMap();

