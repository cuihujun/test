
#ifndef __BUFFER_PARSER_HANDLER_H__
#define __BUFFER_PARSER_HANDLER_H__

#define DEBUG
#ifdef DEBUG
#define LOG printf
#else
#define LOG(exp,args...)
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define BYTE unsigned char
const char g_Pulseaudio_HeaderStart[] = {0x03, 0x00, 0x00, 0x00};
const char g_Pulseaudio_HeaderEnd[]   = {0x50, 0x75, 0x6C, 0x73, 0x65, 0x41, 0x75, 0x64, 0x69, 0x6F, 0x20, 0x54, 0x75, 0x6E, 0x6E, 0x65, 0x6C};

#define HEADER_CONTAINTS_SIZE 12
#define HEADER_BLOCK_SIZE 4


#define PARSER_ESDBIT_MASK_BITS   ( 0x000F )
#define PARSER_ESDBIT_BITS8       ( 0x0000 )
#define PARSER_ESDBIT_BITS16      ( 0x0001 )

#define PARSER_ESDBIT_MASK_CHAN   ( 0x00F0 )
#define PARSER_ESDBIT_MONO        ( 0x0010 )
#define PARSER_ESDBIT_STEREO      ( 0x0020 )

#define PARSER_ESDBIT_MASK_SAMPLERATE (0x00FF)

typedef enum _DataTrnsStatus
{
	TCP_DATA_TRANS_ERROR = -1,
	TCP_DATA_TRANS_NULL = 0,
	TCP_DATA_TRANS_INIT,
	TCP_DATA_TRANS_PULSE
}DataTrnsStatus;

typedef enum _BitRate
{
	PARSER_ESD_BITRATE_ERROR = -1,
	PARSER_ESD_BITS8 = 8,
	PARSER_ESD_BITS16 = 16
}BitRate;

typedef enum _ChannelType
{
	PARSER_ESD_CHANNEL_ERROR = -1,
	PARSER_ESD_MONO = 1,
	PARSER_ESD_STEREO  = 2
}ChannelType;

typedef struct _ESDInfo
{
	BitRate _m_bitRate;
	ChannelType _m_channelType;
	int32_t _m_sampleRate;
}ESDInfo;

class CBufferParserHandler
{
private:
	DataTrnsStatus _m_status;
	ESDInfo* Info;
	void ParseFormat(char* p);
	void ParseSampleRate(char* p);
	void SetDataTransStatus(DataTrnsStatus status)
	{
		_m_status = status;
	}
	void SetBitRate(BitRate bitrate)
	{
		Info->_m_bitRate = bitrate;
	}
	void SetChannelType(ChannelType channeltype)
	{
		Info->_m_channelType = channeltype;
	}
	void SetSampleRate(int32_t samplerate )
	{
		Info->_m_sampleRate = samplerate;
	}
public:
	CBufferParserHandler()
	{
		_m_status = TCP_DATA_TRANS_INIT;
		Info = new ESDInfo();
	}
	~CBufferParserHandler()
	{
		delete Info;
		LOG("~CBufferParserHandler\n");
	}
	DataTrnsStatus GetDataTransStatus()
	{
		return _m_status;
	}
	BitRate GetBitRate()
	{
		return Info->_m_bitRate;
	}

	ChannelType GetChannelType()
	{
		return Info->_m_channelType;
	}

	int32_t GetSampleRate()
	{
		return Info->_m_sampleRate;
	}
	
	size_t GetLengthOfthePulseHead()
	{
		return sizeof(g_Pulseaudio_HeaderEnd);
	}

	DataTrnsStatus ParserPulseHeader_SearchFromTail(char *buffer, size_t length);
	DataTrnsStatus ParserPulseHeader_SearchFromHead(char *buffer, size_t length);
};

#endif