#pragma once

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include "JpegDecoder.h"
#include "DicomDictionary.h"
#include <QObject>
#include <map>

using namespace std;

class CDecoder : public QObject
{

	Q_OBJECT

public:
	CDecoder(void);
	~CDecoder(void);

// some data element tags according PS 3.6
static const unsigned int PIXEL_REPRESENTATION = 0x00280103,
						  TRANSFER_SYNTAX_UID = 0x00020010,
						  MODALITY = 0x00080060,

						  IMAGE_POSITION = 0x00200032,
						  IMAGE_ORIENTATION = 0x00200035, // retired
						  IMAGE_ORIENTATION_PATIENT = 0x00200037,

						  SLICE_THICKNESS = 0x00180050,
						  SLICE_SPACING = 0x00180088,

						  SAMPLES_PER_PIXEL = 0x00280002,
						  PHOTOMETRIC_INTERPRETATION = 0x00280004,
						  PLANAR_CONFIGURATION = 0x00280006,
						  NUMBER_OF_FRAMES = 0x00280008,
						  ROWS = 0x00280010,
						  COLUMNS = 0x00280011,
						  PIXEL_SPACING = 0x00280030,

						  BITS_ALLOCATED = 0x00280100,

						  WINDOW_CENTER = 0x00281050,
						  WINDOW_WIDTH = 0x00281051,
						  RESCALE_INTERCEPT = 0x00281052,
						  RESCALE_SLOPE = 0x00281053,
						  RED_PALETTE = 0x00281201,
						  GREEN_PALETTE = 0x00281202,
						  BLUE_PALETTE = 0x00281203,
						  ICON_IMAGE_SEQUENCE = 0x00880200,
						  PIXEL_DATA = 0x7FE00010,

						  PATIENTS_NAME = 0x00100010,
						  PATIENT_ID = 0x00100020,
						  PATIENTS_BIRTHDATE = 0x00100030,
						  PATIENTS_SEX = 0x00100040;


// common Value Representations
static const int
            AE = 0x4145,
            AS = 0x4153,
            AT = 0x4154,
            CS = 0x4353,
            DA = 0x4441,
            DS = 0x4453,
            DT = 0x4454,
            FD = 0x4644,
            FL = 0x464C,
            IS = 0x4953,
            LO = 0x4C4F,
            LT = 0x4C54,
            PN = 0x504E,
            SH = 0x5348,
            SL = 0x534C,
            SS = 0x5353,
            ST = 0x5354,
            TM = 0x544D,
            UI = 0x5549,
            UL = 0x554C,   
            US = 0x5553,
            UT = 0x5554,
            OB = 0x4F42,
            OW = 0x4F57,
            SQ = 0x5351,
            UN = 0x554E,
            QQ = 0x3F3F;

static const map<unsigned int, string> dictionary;


/*There are three special SQ related Data Elements that are not ruled by the VR encoding rules
conveyed by the Transfer Syntax. They shall be encoded as Implicit VR. NEMA DICOM 3.0*/
static const unsigned int ITEM = 0xFFFEE000;
static const unsigned int ITEM_DELIMITATION = 0xFFFEE00D;
static const unsigned int SEQUENCE_DELIMITATION = 0xFFFEE0DD;

//String dicomFileName;
static const int FIRST_OFFSET = 128;
static const string DICM;

private:

	//CDicomDictionary m_dic;
	//CJpegDecoder m_jpeg;
	long m_position;  // для чтения сжатого jpg


	char *m_fragment; // I needed 1 byte data type

	//public List<string> dicomInfo;

	ifstream m_dicomFile;

	bool m_readingDataElements;
	bool m_oddLocations;
	
	bool m_inSequence;
	bool m_itemDelimiter;
	bool m_sequenceDelimiter;

	bool m_littleEndian;
	bool m_delimiter;

	int m_elementLength; // because can be negative despite the fact that is a length value
    unsigned int m_vr; // Data Item VR
	unsigned int m_tag; // Data Item tag

	int m_min8;
	int m_min16;

	static const int m_IMPLICIT_VR = 0x2D2D; 

    int m_offset;

	string m_photoInterpretation;
    
	//List<byte> pixels8;
	//List<ushort> pixels16;
    
	int m_ctrPixels;



	string m_patientsName;
	string m_patientID;
	string m_patientsBirthdate;
	string m_patientsSex;

	string m_sliceThikness; // temp type
	string m_sliceSpasing; // temp type

	string m_imagePosition; // temp type
	string m_imageOrientation; // temp type
	string m_imageOrientationPatient; // temp type

	//--------------------------------
	string GetString(int);

	unsigned int ReadTag();

	int ReadElementLength();

	unsigned int ReadInt();

	unsigned short ReadUShort();

	unsigned char ReadByte();

	void ReadSequence();
	void ReadItem();
	void TrySkipSequence();
	void SkipBytes(const int&);

	void AddInfo(const unsigned int& tag, string& value);
	char* GetString(); 

public:

	double m_rescaleIntercept;
	double m_rescaleSlope;

	unsigned short m_bitsAllocated;

	int m_width;
	int m_height;

	int m_nImages;
	int m_samplesPerPixel;
	unsigned short m_pixelRepresentation;

	int m_location;

	static double m_pixelDepth;
	static double m_pixelWidth;
	static double m_pixelHeight;

	bool m_dicomFileReadSuccess;
	bool m_compressedImage; 
	bool m_dicomDir;
	bool m_signedImage;

	double m_windowCentre;
	double m_windowWidth;

	string m_unit;

public slots:

	void ReadFile(QString); 
};

