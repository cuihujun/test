

#include "BufferParserHandler.h"

void CBufferParserHandler::ParseFormat(char *p)
{
	SetBitRate(((p[0] & PARSER_ESDBIT_MASK_BITS) == PARSER_ESDBIT_BITS16) ? PARSER_ESD_BITS16 : PARSER_ESD_BITS8);
	SetChannelType(((p[0] & PARSER_ESDBIT_MASK_CHAN) == PARSER_ESDBIT_MONO) ? PARSER_ESD_MONO : PARSER_ESD_STEREO);

	LOG("[BufferParserHandler.cpp]bitRate = %d\n", GetBitRate());
	LOG("[BufferParserHandler.cpp]channelType = %d\n", GetChannelType());
	//LOG("[BufferParserHandler.cpp]0x%02x\n",p[0]);
	//LOG("[BufferParserHandler.cpp]0x%02x\n",p[1]);
}

void CBufferParserHandler::ParseSampleRate(char *p)
{
	//SetSampleRate(p[0] & PARSER_ESDBIT_MASK_SAMPLERATEU);
	
	BYTE bSampleRate[4] = 
	{
		p[3]&PARSER_ESDBIT_MASK_SAMPLERATE, p[2]&PARSER_ESDBIT_MASK_SAMPLERATE, 
		p[1]&PARSER_ESDBIT_MASK_SAMPLERATE, p[0]&PARSER_ESDBIT_MASK_SAMPLERATE
	};
	int32_t SampleRate = 0;
	
	SampleRate = bSampleRate[3];
	SampleRate |= bSampleRate[2] << 8;
	SampleRate |= bSampleRate[1] << 16;
	SampleRate |= bSampleRate[0] << 24;

	SetSampleRate(SampleRate);
	LOG("[BufferParserHandler.cpp]sampleRate = %d\n", GetSampleRate());
}
	
DataTrnsStatus CBufferParserHandler::ParserPulseHeader_SearchFromTail(char *buffer, size_t length)
{
	assert(buffer != NULL);
	assert(length);
	
	LOG("[BufferParserHandler.cpp]The buffer lenght you provide is %d\n", length);
	if(GetDataTransStatus() == TCP_DATA_TRANS_PULSE)
	{
		return TCP_DATA_TRANS_PULSE;
	}
	
	if(length < sizeof(g_Pulseaudio_HeaderEnd)+HEADER_CONTAINTS_SIZE)
	{
		return TCP_DATA_TRANS_INIT;
	}
	
	char *p;
    for (int searchingPosition = 0; p <= (buffer-sizeof(g_Pulseaudio_HeaderEnd)+length); searchingPosition++)
    {
		p = buffer + searchingPosition;
        if (memcmp(p, g_Pulseaudio_HeaderEnd, sizeof(g_Pulseaudio_HeaderEnd)) == 0)
        {
			p = buffer + searchingPosition - HEADER_CONTAINTS_SIZE;
			if (memcmp(p, g_Pulseaudio_HeaderStart, sizeof(g_Pulseaudio_HeaderStart)) == 0)
			{
				ParseFormat(p + HEADER_BLOCK_SIZE);
				ParseSampleRate(p + HEADER_BLOCK_SIZE*2);
				
				SetDataTransStatus(TCP_DATA_TRANS_PULSE); /* found */
			}
            return GetDataTransStatus();
        }
    }
	return GetDataTransStatus();
}


DataTrnsStatus CBufferParserHandler::ParserPulseHeader_SearchFromHead(char *buffer, size_t length)
{
	assert(buffer != NULL);
	assert(length);
	
	LOG("[BufferParserHandler.cpp]The buffer lenght you provide is %d\n", length);
	if(GetDataTransStatus() == TCP_DATA_TRANS_PULSE)
	{
		return TCP_DATA_TRANS_PULSE;
	}
	
	if(length < sizeof(g_Pulseaudio_HeaderEnd)+HEADER_CONTAINTS_SIZE)
	{
		return TCP_DATA_TRANS_INIT;
	}
	
	char *p;
    for (int searchingPosition = 0; p <= (buffer-sizeof(g_Pulseaudio_HeaderStart)+length); searchingPosition++)
    {
		p = buffer + searchingPosition;
        if (memcmp(p, g_Pulseaudio_HeaderStart, sizeof(g_Pulseaudio_HeaderStart)) == 0)
        {
			p = buffer + searchingPosition + HEADER_CONTAINTS_SIZE;
			if (memcmp(p, g_Pulseaudio_HeaderEnd, sizeof(g_Pulseaudio_HeaderEnd)) == 0)
			{
				p = buffer + searchingPosition;
				ParseFormat(p + HEADER_BLOCK_SIZE);
				ParseSampleRate(p + HEADER_BLOCK_SIZE*2);
				
				SetDataTransStatus(TCP_DATA_TRANS_PULSE); /* found */
			}
            return GetDataTransStatus();
        }
    }
	return GetDataTransStatus();
}



















