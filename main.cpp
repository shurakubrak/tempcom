#include <iostream>
#include <string>
#include <cassert>
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
			fd = fopen(fn.c_str(), "r");
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
		if(r == 'y' || r == 'Y'){
			;
		}

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
	cout << "Calibration:" << endl;
	cout << "_EEPROM_Flags = " << to_string(data->_EEPROM_Flags) << endl;
	cout << "_MC_U1 = " << to_string(data->_MC_U1) << endl; 
	cout << "_MC_Q1 = " << to_string(data->_MC_Q1) << endl;
	cout << "_MC_U2 = " << to_string(data->_MC_U2) << endl;
	cout << "_MC_Q2 = " << to_string(data->_MC_Q2) << endl;
	cout << "_MC_U3 = " << to_string(data->_MC_U3) << endl;
	cout << "_MC_Q3 = " << to_string(data->_MC_Q3) << endl;
	cout << "_MC_U4 = " << to_string(data->_MC_U4) << endl;
	cout << "_MC_Q4 = " << to_string(data->_MC_Q4) << endl;
	cout << "_MC_U5 = " << to_string(data->_MC_U5) << endl;

	cout << endl;
	cout << "Account:" << endl;
	cout << "_MC_DU = " << to_string(data->_MC_DU) << endl;
	cout << "_MC_InFilt_Kp = " << to_string(data->_MC_InFilt_Kp) << endl;
	cout << "_MI_Clock_Divisor = " << to_string(data->_MI_Clock_Divisor) << endl;

	cout << endl;
	cout << "Outputs:" << endl;
	cout << "_ITG_OutputWeight = " << to_string(data->_EEPROM_Flags) << endl;
	cout << "_IFM_Mode = " << to_string(data->_IFM_Mode) << endl;
	cout << "_IFM_Lowest_Value = " << to_string(data->_IFM_Lowest_Value) << endl;
	cout << "_IFM_PulseWeight = " << to_string(data->_IFM_PulseWeight) << endl;
	cout << "_PWM_RangeFI_InLo_ = " << to_string(data->_PWM_RangeFI_InLo_) << endl;
	cout << "_PWM_RangeFI_InHi_ = " << to_string(data->_PWM_RangeFI_InHi_) << endl;
	cout << "_PWM_RangeFI_OutLo_ = " << to_string(data->_PWM_RangeFI_OutLo_) << endl;
	cout << "_PWM_RangeFI_OutHi_ = " << to_string(data->_PWM_RangeFI_OutHi_) << endl;
	cout << "_PWM_RangeIDAC_InLo_ = " << to_string(data->_PWM_RangeIDAC_InLo_) << endl;
	cout << "_PWM_RangeIDAC_InHi_ = " << to_string(data->_PWM_RangeIDAC_InHi_) << endl;
	cout << "_PWM_RangeIDAC_OutLo_ = " << to_string(data->_PWM_RangeIDAC_OutLo_) << endl;
	cout << "_PWM_RangeIDAC_OutHi_ = " << to_string(data->_PWM_RangeIDAC_OutHi_) << endl;
	cout << "_Doze_Level1_10ls = " << to_string(data->_Doze_Level1_10ls) << endl;
	cout << "_MO_CmpLevel1 = " << to_string(data->_MO_CmpLevel1) << endl;
	cout << "_MO_CmpLevel2 = " << to_string(data->_MO_CmpLevel2) << endl;

	cout << endl;
	cout << "System:" << endl;
	cout << "_NetWork_Address = " << to_string(data->_NetWork_Address) << endl;
	cout << "_G_SerialNum_hi = " << to_string(data->_G_SerialNum_hi) << endl;
	cout << "_G_SerialNum = " << to_string(data->_G_SerialNum) << endl;

	cout << endl;
	cout << "Testing (really removed, only for compatibility):" << endl;
	cout << "_MC_Q5 = " << to_string(data->_MC_Q5) << endl;
	cout << "_LCD_ValuesList = " << to_string(data->_LCD_ValuesList) << endl;
	cout << "_LCD_Filter = " << to_string(data->_LCD_Filter) << endl;
	cout << "_LCD_ValuesTime = " << to_string(data->_LCD_ValuesTime) << endl;
	cout << "_KBD_List[4] = " << to_string(data->_KBD_List[0])
		<< ", " << to_string(data->_KBD_List[1])
		<< ", " << to_string(data->_KBD_List[2])
		<< ", " << to_string(data->_KBD_List[3]) << endl;
	cout << "_Doze_Level2_10ls = " << to_string(data->_Doze_Level2_10ls) << endl;
	cout << "_eTime_Stamp = " << to_string(data->_eTime_Stamp) << endl;
	cout << "_iTime_Stamp = " << to_string(data->_iTime_Stamp) << endl;
}