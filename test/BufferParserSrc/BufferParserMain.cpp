







#include "BufferParserHandler.h"


int main()
{
	int result;
	CBufferParserHandler *BufferHandler = new CBufferParserHandler();

	FILE* fp;
	char buff[29];
	fp=fopen("./testfile_same_29byte", "rb");
	fread(buff, sizeof(char), 29, fp);
	fclose(fp);
	printf("%d\n", sizeof(buff));
	result = BufferHandler->ParserPulseHeader_SearchFromHead(buff, sizeof(buff));
	printf("result1 = %d\n", result);
	printf("BufferHandler->GetDataTransStatus() = %d\n", BufferHandler->GetDataTransStatus());
	delete BufferHandler;
	return 0;
	
}

























