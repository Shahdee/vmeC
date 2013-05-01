#include "StdAfx.h"
#include "Decoder.h"
#include "DicomDictionary.h"
#include <string>

CDecoder::CDecoder(void)
{
	m_littleEndian = true;
	m_compressedImage = false;
	m_signedImage = false;
    m_dicomFileReadSuccess = false;
    m_readingDataElements = true;
    m_oddLocations = false;
	m_delimiter = false;
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
		//case OR:
		case UN:{	  
				 if(b2 ==0 && b3 ==0){
					return ReadInt();
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

void CDecoder::ReadFile(QString path)
{
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

				// it is assumed that DICOM default transfer syntax is implicit VR, little endian

				m_elementLength = ReadElementLength();

				/*
				if (m_elementLength == -1 && tag != PIXEL_DATA){
                    m_elementLength = 0;
                    m_inSequence = true;
                }

				if ((m_location & 1) != 0){
                    m_oddLocations = true;
				}

                if (m_inSequence){
                    //AddInfo(tag, null);                     
                    continue;
                }*/

				
				switch (tag)
				{
					case 
				
				}

				system("pause");

			}
		}
	}
}


const string CDecoder::ITEM = "FFFEE000";
const string CDecoder::ITEM_DELIMITATION = "FFFEE00D";
const string CDecoder::SEQUENCE_DELIMITATION ="FFFEE0DD";
const string CDecoder::DICM = "DICM";


double CDecoder::m_pixelDepth = 1.0;
double CDecoder::m_pixelWidth = 1.0;
double CDecoder::m_pixelHeight = 1.0f;



const map<unsigned short, string> CDecoder::dictionary = CDicomDictionary::InitMap();

