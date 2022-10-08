#include <iostream>
#include <string>
#include "main.h"

using namespace std;

int main(int, char**) 
{
	try
	{
		FILE* fd;
		fpos_t position;
		while(true){
			cout << "Enter file name (current folder only):";
			string fn;
			cin >> fn;
			/*open file data*/
			fd = fopen(fn.c_str(), "rb");
			if(fd == NULL){
				cout << "Error: file not found" << endl;
				continue;;
			}
			fgetpos(fd, &position);
		
			/*size calculation*/
			int n = 0;
			while (fgetc(fd) != EOF) 
    	  		++n;
	    	if (feof(fd)) {
      			cout << "Total number of bytes read: " << n << endl;
			if(n != SZ){
				cout << " This size fail";
				continue;	
			}
    		}
			break;
		}
		
		/*read data*/
		char bf[SZ];
		fsetpos(fd, &position);
		for(size_t i=0; i<SZ; i++)
			bf[i] = fgetc(fd);
		fclose(fd);

		Print_EEP((EEP_ParamStruct*)bf);

		cout << "Save result to file 'result.txt' (y/n):";
		char r;
		cin >> r;
		if(r == 'y' || r == 'Y')
			Save_Result((EEP_ParamStruct*)bf);
		
		return 0;
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
        return -1;
	}
}
/*********************************************/

void Print_EEP(EEP_ParamStruct* data)
{
	cout << "Calibration:" << endl
	<< "	_EEPROM_Flags = " << to_string(data->_EEPROM_Flags) << endl
	<< "	_MC_U1 = " << to_string(data->_MC_U1) << endl
	<< "	_MC_Q1 = " << to_string(data->_MC_Q1) << endl
	<< "	_MC_U2 = " << to_string(data->_MC_U2) << endl
	<< "	_MC_Q2 = " << to_string(data->_MC_Q2) << endl
	<< "	_MC_U3 = " << to_string(data->_MC_U3) << endl
	<< "	_MC_Q3 = " << to_string(data->_MC_Q3) << endl
	<< "	_MC_U4 = " << to_string(data->_MC_U4) << endl
	<< "	_MC_Q4 = " << to_string(data->_MC_Q4) << endl
	<< "	_MC_U5 = " << to_string(data->_MC_U5) << endl;

	cout << endl;
	cout << "Account:" << endl
	<< "	_MC_DU = " << to_string(data->_MC_DU) << endl
	<< "	_MC_InFilt_Kp = " << to_string(data->_MC_InFilt_Kp) << endl
	<< "	_MI_Clock_Divisor = " << to_string(data->_MI_Clock_Divisor) << endl;

	cout << endl;
	cout << "Outputs:" << endl
	<< "	_ITG_OutputWeight = " << to_string(data->_EEPROM_Flags) << endl
	<< "	_IFM_Mode = " << to_string(data->_IFM_Mode) << endl
	<< "	_IFM_Lowest_Value = " << to_string(data->_IFM_Lowest_Value) << endl
	<< "	_IFM_PulseWeight = " << to_string(data->_IFM_PulseWeight) << endl
	<< "	_PWM_RangeFI_InLo_ = " << to_string(data->_PWM_RangeFI_InLo_) << endl
	<< "	_PWM_RangeFI_InHi_ = " << to_string(data->_PWM_RangeFI_InHi_) << endl
	<< "	_PWM_RangeFI_OutLo_ = " << to_string(data->_PWM_RangeFI_OutLo_) << endl
	<< "	_PWM_RangeFI_OutHi_ = " << to_string(data->_PWM_RangeFI_OutHi_) << endl
	<< "	_PWM_RangeIDAC_InLo_ = " << to_string(data->_PWM_RangeIDAC_InLo_) << endl
	<< "	_PWM_RangeIDAC_InHi_ = " << to_string(data->_PWM_RangeIDAC_InHi_) << endl
	<< "	_PWM_RangeIDAC_OutLo_ = " << to_string(data->_PWM_RangeIDAC_OutLo_) << endl
	<< "	_PWM_RangeIDAC_OutHi_ = " << to_string(data->_PWM_RangeIDAC_OutHi_) << endl
	<< "	_Doze_Level1_10ls = " << to_string(data->_Doze_Level1_10ls) << endl
	<< "	_MO_CmpLevel1 = " << to_string(data->_MO_CmpLevel1) << endl
	<< "	_MO_CmpLevel2 = " << to_string(data->_MO_CmpLevel2) << endl;

	cout << endl;
	cout << "System:" << endl
	<< "	_NetWork_Address = " << to_string(data->_NetWork_Address) << endl
	<< "	_G_SerialNum_hi = " << to_string(data->_G_SerialNum_hi) << endl
	<< "	_G_SerialNum = " << to_string(data->_G_SerialNum) << endl;

	cout << endl;
	cout << "Testing (really removed, only for compatibility):" << endl
	<< "	_MC_Q5 = " << to_string(data->_MC_Q5) << endl
	<< "	_LCD_ValuesList = " << to_string(data->_LCD_ValuesList) << endl
	<< "	_LCD_Filter = " << to_string(data->_LCD_Filter) << endl
	<< "	_LCD_ValuesTime = " << to_string(data->_LCD_ValuesTime) << endl
	<< "	_KBD_List[4] = " << to_string(data->_KBD_List[0])
		<< ", " << to_string(data->_KBD_List[1])
		<< ", " << to_string(data->_KBD_List[2])
		<< ", " << to_string(data->_KBD_List[3]) << endl
	<< "	_Doze_Level2_10ls = " << to_string(data->_Doze_Level2_10ls) << endl
	<< "	_eTime_Stamp = " << to_string(data->_eTime_Stamp) << endl
	<< "	_iTime_Stamp = " << to_string(data->_iTime_Stamp) << endl;
}
/************************************************************/

void Save_Result(EEP_ParamStruct* data)
{
	FILE* fd;
	fd = fopen("result.txt", "w");
	if(fd == nullptr){
		perror("Eroor file result.");
		return;
	}

	fputs("Calibration:\n", fd);
	fputs(("	_EEPROM_Flags = " + to_string(data->_EEPROM_Flags) + '\n').c_str(), fd);
	fputs(("	_MC_U1 = " + to_string(data->_MC_U1) + '\n').c_str(), fd); 
	fputs(("	_MC_Q1 = " + to_string(data->_MC_Q1) + '\n').c_str(), fd);
	fputs(("	_MC_U2 = " + to_string(data->_MC_U2) + '\n').c_str(), fd);
	fputs(("	_MC_Q2 = " + to_string(data->_MC_Q2) + '\n').c_str(), fd);
	fputs(("	_MC_U3 = " + to_string(data->_MC_U3) + '\n').c_str(), fd);
	fputs(("	_MC_Q3 = " + to_string(data->_MC_Q3) + '\n').c_str(), fd);
	fputs(("	_MC_U4 = " + to_string(data->_MC_U4) + '\n').c_str(), fd);
	fputs(("	_MC_Q4 = " + to_string(data->_MC_Q4) + '\n').c_str(), fd);
	fputs(("	_MC_U5 = " + to_string(data->_MC_U5) + '\n').c_str(), fd);

	fputs("\n", fd);
	fputs("Account:\n", fd);
	fputs(("	_MC_DU = " + to_string(data->_MC_DU) + '\n').c_str(), fd);
	fputs(("	_MC_InFilt_Kp = " + to_string(data->_MC_InFilt_Kp) + '\n').c_str(), fd);
	fputs(("	_MI_Clock_Divisor = " + to_string(data->_MI_Clock_Divisor) + '\n').c_str(), fd);

	fputs("\n", fd);
	fputs("Outputs:\n", fd);
	fputs(("	_ITG_OutputWeight = " + to_string(data->_EEPROM_Flags) + '\n').c_str(), fd);
	fputs(("	_IFM_Mode = " + to_string(data->_IFM_Mode) + '\n').c_str(), fd);
	fputs(("	_IFM_Lowest_Value = " + to_string(data->_IFM_Lowest_Value) + '\n').c_str(), fd);
	fputs(("	_IFM_PulseWeight = " + to_string(data->_IFM_PulseWeight) + '\n').c_str(), fd);
	fputs(("	_PWM_RangeFI_InLo_ = " + to_string(data->_PWM_RangeFI_InLo_) + '\n').c_str(), fd);
	fputs(("	_PWM_RangeFI_InHi_ = " + to_string(data->_PWM_RangeFI_InHi_) + '\n').c_str(), fd);
	fputs(("	_PWM_RangeFI_OutLo_ = " + to_string(data->_PWM_RangeFI_OutLo_) + '\n').c_str(), fd);
	fputs(("	_PWM_RangeFI_OutHi_ = " + to_string(data->_PWM_RangeFI_OutHi_) + '\n').c_str(), fd);
	fputs(("	_PWM_RangeIDAC_InLo_ = " + to_string(data->_PWM_RangeIDAC_InLo_) + '\n').c_str(), fd);
	fputs(("	_PWM_RangeIDAC_InHi_ = " + to_string(data->_PWM_RangeIDAC_InHi_) + '\n').c_str(), fd);
	fputs(("	_PWM_RangeIDAC_OutLo_ = " + to_string(data->_PWM_RangeIDAC_OutLo_) + '\n').c_str(), fd);
	fputs(("	_PWM_RangeIDAC_OutHi_ = " + to_string(data->_PWM_RangeIDAC_OutHi_) + '\n').c_str(), fd);
	fputs(("	_Doze_Level1_10ls = " + to_string(data->_Doze_Level1_10ls) + '\n').c_str(), fd);
	fputs(("	_MO_CmpLevel1 = " + to_string(data->_MO_CmpLevel1) + '\n').c_str(), fd);
	fputs(("	_MO_CmpLevel2 = " + to_string(data->_MO_CmpLevel2) + '\n').c_str(), fd);

	fputs("\n", fd);
	fputs("System:\n", fd);
	fputs(("	_NetWork_Address = " + to_string(data->_NetWork_Address) + '\n').c_str(), fd);
	fputs(("	_G_SerialNum_hi = " + to_string(data->_G_SerialNum_hi) + '\n').c_str(), fd);
	fputs(("	_G_SerialNum = " + to_string(data->_G_SerialNum) + '\n').c_str(), fd);

	fputs("\n", fd);
	fputs("Testing (really removed, only for compatibility):\n", fd);
	fputs(("	_MC_Q5 = " + to_string(data->_MC_Q5) + '\n').c_str(), fd);
	fputs(("	_LCD_ValuesList = " + to_string(data->_LCD_ValuesList) + '\n').c_str(), fd);
	fputs(("	_LCD_Filter = " + to_string(data->_LCD_Filter) + '\n').c_str(), fd);
	fputs(("	_LCD_ValuesTime = " + to_string(data->_LCD_ValuesTime) + '\n').c_str(), fd);
	fputs(("	_KBD_List[4] = " + to_string(data->_KBD_List[0])
		+ ", " + to_string(data->_KBD_List[1])
		+ ", " + to_string(data->_KBD_List[2])
		+ ", " + to_string(data->_KBD_List[3]) + '\n').c_str(), fd);
	fputs(("	_Doze_Level2_10ls = " + to_string(data->_Doze_Level2_10ls) + '\n').c_str(), fd);
	fputs(("	_eTime_Stamp = " + to_string(data->_eTime_Stamp) + '\n').c_str(), fd);
	fputs(("	_iTime_Stamp = " + to_string(data->_iTime_Stamp) + '\n').c_str(), fd);

	fclose(fd);
}