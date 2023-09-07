#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>

void Gen_Menu(){
	printf("1.Choose location option\n");
	printf("2.Generate file Register_S32K144.h\n");
	printf("3.Exits\n");
}

int Gen_Check(char f_CharA_aa[], char f_CharB_aa[]){
	unsigned int f_LenA_u32 = strlen(f_CharA_aa);
	char f_CharC_aa[f_LenA_u32+1];
	
	for(int i=0;i<f_LenA_u32;i++){
		f_CharC_aa[i]=f_CharB_aa[i];
	}
	f_CharC_aa[f_LenA_u32]='\0';
	return strcmp(f_CharA_aa,f_CharC_aa);
}

void Gen_Time(FILE* a){
	time_t curtime;
	time(&curtime);
	printf("%s", ctime(&curtime));
	fprintf(a,"%s", ctime(&curtime));
}

int Gen_HexToDec(char f_Hex_aa[]) {
    unsigned int f_Dec_u32 = 0;
    unsigned int f_Value_u32;
    unsigned int f_Power_u32 = 1;
    unsigned int f_HexLength_u32 = strlen(f_Hex_aa);
    for (int i = f_HexLength_u32 - 1; i >= 0; i--) {
        if (f_Hex_aa[i] >= '0' && f_Hex_aa[i] <= '9'){
            f_Value_u32 = f_Hex_aa[i] - '0';
        } 
        else if (f_Hex_aa[i] >= 'A' && f_Hex_aa[i] <= 'F'){
            f_Value_u32 = f_Hex_aa[i] - 'A' + 10;
        } 
        f_Dec_u32 += f_Value_u32*f_Power_u32;
        f_Power_u32*=16;
    }
    return f_Dec_u32;
}


int Gen_Dummy(char f_CharA_aa[],char f_CharB_aa[]){
	int f_LenA_u32 = strlen(f_CharA_aa);
	int f_LenB_u32 = strlen(f_CharB_aa);
	char f_CharC_aa[f_LenA_u32-1];
	char f_CharD_aa[f_LenB_u32-1];
	int f_N_u32=2, f_M_u32=2;
	for(int i=0;i<f_LenA_u32-2;i++){
		f_CharC_aa[i]=f_CharA_aa[f_N_u32];
		f_N_u32++;
	}
	f_CharC_aa[f_LenA_u32-2]='\0';
	for(int i=0;i<f_LenB_u32-2;i++){
		f_CharD_aa[i]=f_CharB_aa[f_M_u32];
		f_M_u32++;
	}
	f_CharD_aa[f_LenB_u32-2]='\0';
	return Gen_HexToDec(f_CharD_aa)-Gen_HexToDec(f_CharC_aa);
}

typedef struct infor{
    char Base_Address[100];
    char Peripheral_Name[20];
    char Offset[20];
    char Register_name[50];
    int Width;
    char Access[5];
}INFOR;



char l_Now_aa[6]="<NOW>";
char l_Msn_aa[6]="<MSN>";
const char l_Ro_aa[4]="RO\n";



int main(){
	char l_input_aa[100], l_output_aa[100];
	l_input_aa[1]='0';
	while(1){
		Gen_Menu();
		int l_choose_u32;
		printf("Enter the number: ");
		scanf("%d", &l_choose_u32);
		
		if(l_choose_u32 == 1){
			printf("1.1 Set input file location (file name): ");
			scanf("%s", l_input_aa);
			printf("1.2 Set output file location (file name): ");
			scanf("%s", l_output_aa);
		}
		
		else if(l_choose_u32==2 && l_input_aa[1] == '0'){
			printf("No input!!\n");
		}
		
		else if(l_choose_u32==2 && l_input_aa[1] != '0'){	
			char l_CharC_aa[100];
    		FILE* l_in_ptr;
    		FILE* l_out_ptr;
    		char *l_sp_ptr;
    		INFOR l_a_st[1000];
    		INFOR l_a2_st[1000];
    		
    		l_out_ptr = fopen(l_output_aa,"w");		//"Register_S32K144.h"
    		if(l_out_ptr==NULL){
        		printf("Error");
    		}
    		
    		l_in_ptr = fopen(l_input_aa,"r");		//"Register_S32K144.csv"
    		if(l_in_ptr==NULL){
        		printf("Error");
    		}
	
			fgets(l_CharC_aa,100,l_in_ptr);
    		int l_j_u32=0;
    		int l_i_u32=0;
    		
    		fgets(l_CharC_aa,100,l_in_ptr);
    		l_sp_ptr = strtok(l_CharC_aa,",");
    		strcpy(l_a2_st[l_j_u32].Base_Address,l_sp_ptr);
    		l_sp_ptr = strtok(NULL,",");
   			strcpy(l_a2_st[l_j_u32].Peripheral_Name,l_sp_ptr);
    		l_sp_ptr = strtok(NULL,",");
    		strcpy(l_a_st[l_i_u32].Offset,l_sp_ptr);
    		l_sp_ptr = strtok(NULL,",");
    		strcpy(l_a_st[l_i_u32].Register_name,l_sp_ptr);
    		l_sp_ptr = strtok(NULL,",");
    		l_a_st[l_i_u32].Width = atoi(l_sp_ptr);
    		l_sp_ptr = strtok(NULL,",");
    		strcpy(l_a_st[l_i_u32].Access,l_sp_ptr);
    //printf("%s %s %s %s %d %s %d", l_a2_st[l_j_u32].Base_Address, l_a2_st[l_j_u32].Peripheral_Name, l_a_st[l_i_u32].Offset, l_a_st[l_i_u32].Register_name, l_a_st[l_i_u32].Width, l_a_st[l_i_u32].Access,strcmp(l_a_st[l_i_u32].Access,l_Ro_aa));
    		l_j_u32++;
   			l_i_u32++;
			FILE* l_template_ptr;
			char l_c_read_aa[100];
			l_template_ptr = fopen("Template.txt","r");
			if(l_template_ptr==NULL){
				printf("Error");
    		}    
    		while(!feof(l_template_ptr)){
    			fgets(l_c_read_aa,100,l_template_ptr);
    			int l_n_read_u32=0;
    			char l_b_read_aa[100];
    			char l_temp_aa[6];
    			int l_j_cnt_u32;
    			int l_ok_u32 = 0;
    			
    			while(l_c_read_aa[l_n_read_u32]!='\0'){
    				l_b_read_aa[l_n_read_u32]=l_c_read_aa[l_n_read_u32];
    				l_n_read_u32++;
				}
				
				l_b_read_aa[l_n_read_u32]='\0';
				for(int i=0;i<l_n_read_u32;i++){
					
					if(l_b_read_aa[i]=='<'){
						l_j_cnt_u32=i;
						
						for(int m=0;m<6;m++){
							l_temp_aa[m]=l_b_read_aa[i];
							i++;
						}
						
						i=l_j_cnt_u32;
						l_temp_aa[5]='\0';
		
						if(strcmp(l_temp_aa,l_Now_aa)==0){
							l_b_read_aa[l_j_cnt_u32]='\0';
							l_ok_u32=1;
						}
						
						else if(strcmp(l_temp_aa,l_Msn_aa)==0){	
							l_ok_u32=2;
							printf("/* %s */\n",l_a2_st[0].Peripheral_Name);
							fprintf(l_out_ptr,"/* %s */\n",l_a2_st[0].Peripheral_Name);
						}
					}
				}
				
				if(l_ok_u32==2){
    				break;
				}
    			
				printf("%s", l_b_read_aa);
    			fprintf(l_out_ptr,"%s", l_b_read_aa);
    			
				if(l_ok_u32==1){
    				Gen_Time(l_out_ptr);
				}
			}

	    	while(!feof(l_in_ptr)){   
				fgets(l_CharC_aa,100,l_in_ptr);
				
				if(l_CharC_aa[0]==','){
					int l_n_u32=0;
    				int l_m_u32=2;
    				char l_CharB_aa[100];
    				
    				while(l_CharC_aa[l_m_u32]!='\0'){
        			l_CharB_aa[l_n_u32++]=l_CharC_aa[l_m_u32++];

    				}
    				
    				l_CharB_aa[l_n_u32]='\0';
    				l_sp_ptr = strtok(l_CharB_aa,",");
    				strcpy(l_a_st[l_i_u32].Offset,l_sp_ptr);
    				l_sp_ptr = strtok(NULL,",");
    				strcpy(l_a_st[l_i_u32].Register_name,l_sp_ptr);
    				l_sp_ptr = strtok(NULL,",");
    				l_a_st[l_i_u32].Width = atoi(l_sp_ptr);
    				l_sp_ptr = strtok(NULL,",");
    				strcpy(l_a_st[l_i_u32].Access,l_sp_ptr);
    //printf("%s %s %d %s", a[i].Offset, a[i].Register_name, a[i].Width, a[i].Access);
    				l_i_u32++;
				}
				
				else if(l_CharC_aa[0]=='0'){
					l_sp_ptr = strtok(l_CharC_aa,",");
   					strcpy(l_a2_st[l_j_u32].Base_Address,l_sp_ptr);
    				l_sp_ptr = strtok(NULL,",");
    				strcpy(l_a2_st[l_j_u32].Peripheral_Name,l_sp_ptr);
    				l_sp_ptr = strtok(NULL,",");
    				strcpy(l_a_st[l_i_u32].Offset,l_sp_ptr);
    				l_sp_ptr = strtok(NULL,",");
    				strcpy(l_a_st[l_i_u32].Register_name,l_sp_ptr);
    				l_sp_ptr = strtok(NULL,",");
    				l_a_st[l_i_u32].Width = atoi(l_sp_ptr);
    				l_sp_ptr = strtok(NULL,",");
    				strcpy(l_a_st[l_i_u32].Access,l_sp_ptr);
    //printf("\n%s %s %s %s %d %s \n", a2[j].Base_Address, a2[j].Peripheral_Name, a[i].Offset, a[i].Register_name, a[i].Width, a[i].Access,i);
    				l_j_u32++;
    				l_i_u32++;
				}
				
				else{
					break;	
				}
			}	
			printf("typedef struct {\n");
			fprintf(l_out_ptr,"typedef struct {\n");
			int l_h_u32=0;
			int l_dummy_u32=0;
			for(int k=0;k<l_i_u32;k++){
				if(Gen_Check(l_a2_st[l_h_u32].Peripheral_Name,l_a_st[k].Register_name)==0){
					if(strcmp(l_a_st[k].Access,l_Ro_aa)==0){
						printf("volatile const unsigned int %s;\n",l_a_st[k].Register_name);
						fprintf(l_out_ptr,"volatile const unsigned int %s;\n",l_a_st[k].Register_name);
							if(Gen_Dummy(l_a_st[k].Offset,l_a_st[k+1].Offset)>4 && Gen_Check(l_a2_st[l_h_u32].Peripheral_Name,l_a_st[k+1].Register_name)==0){
								printf("unsigned int dummy%d[%d];\n",l_dummy_u32,((Gen_Dummy(l_a_st[k].Offset,l_a_st[k+1].Offset)/4)-1));
								fprintf(l_out_ptr,"unsigned int dummy%d[%d];\n",l_dummy_u32++,((Gen_Dummy(l_a_st[k].Offset,l_a_st[k+1].Offset)/4)-1));
							}
					}
					
					else{
						printf("volatile unsigned int %s; \n",l_a_st[k].Register_name);
						fprintf(l_out_ptr,"volatile unsigned int %s; \n",l_a_st[k].Register_name);
						if(Gen_Dummy(l_a_st[k].Offset,l_a_st[k+1].Offset)>4 && Gen_Check(l_a2_st[l_h_u32].Peripheral_Name,l_a_st[k+1].Register_name)==0){
							printf("unsigned int dummy%d[%d];\n",l_dummy_u32,((Gen_Dummy(l_a_st[k].Offset,l_a_st[k+1].Offset)/4)-1));
							fprintf(l_out_ptr,"unsigned int dummy%d[%d];\n",l_dummy_u32++,((Gen_Dummy(l_a_st[k].Offset,l_a_st[k+1].Offset)/4)-1));
						}
					}
				}
				
				else{
					printf("}%s_Type;\n",l_a2_st[l_h_u32].Peripheral_Name);
					fprintf(l_out_ptr,"}%s_Type;\n",l_a2_st[l_h_u32].Peripheral_Name);
					printf("#define %s_BASE_ADDRS (%s)\n",l_a2_st[l_h_u32].Peripheral_Name,l_a2_st[l_h_u32].Base_Address);
					fprintf(l_out_ptr,"#define %s_BASE_ADDRS (%s)\n",l_a2_st[l_h_u32].Peripheral_Name,l_a2_st[l_h_u32].Base_Address);
					printf("#define %s ((%s_Type*)%s_BASE_ADDRS)\n",l_a2_st[l_h_u32].Peripheral_Name,l_a2_st[l_h_u32].Peripheral_Name,l_a2_st[l_h_u32].Peripheral_Name);
					fprintf(l_out_ptr,"#define %s ((%s_Type*)%s_BASE_ADDRS)\n",l_a2_st[l_h_u32].Peripheral_Name,l_a2_st[l_h_u32].Peripheral_Name,l_a2_st[l_h_u32].Peripheral_Name);
					l_h_u32++;
					printf("/* %s */\n",l_a2_st[l_h_u32].Peripheral_Name);
					fprintf(l_out_ptr,"/* %s */\n",l_a2_st[l_h_u32].Peripheral_Name);
					printf("typedef struct {\n");
					fprintf(l_out_ptr,"typedef struct {\n");
					
					if(strcmp(l_a_st[k].Access,l_Ro_aa)==0){
						printf("volatile const unsigned int %s;\n",l_a_st[k].Register_name);
						fprintf(l_out_ptr,"volatile const unsigned int %s;\n",l_a_st[k].Register_name);
						if(Gen_Dummy(l_a_st[k].Offset,l_a_st[k+1].Offset)>4 && Gen_Check(l_a2_st[l_h_u32].Peripheral_Name,l_a_st[k+1].Register_name)==0){
							printf("unsigned int dummy%d[%d];\n",l_dummy_u32,((Gen_Dummy(l_a_st[k].Offset,l_a_st[k+1].Offset)/4)-1));
							fprintf(l_out_ptr,"unsigned int dummy%d[%d];\n",l_dummy_u32++,((Gen_Dummy(l_a_st[k].Offset,l_a_st[k+1].Offset)/4)-1));
						}
					}
					else{
						printf("volatile unsigned int %s; \n",l_a_st[k].Register_name);
						fprintf(l_out_ptr,"volatile unsigned int %s; \n",l_a_st[k].Register_name);
						if(Gen_Dummy(l_a_st[k].Offset,l_a_st[k+1].Offset)>4 && Gen_Check(l_a2_st[l_h_u32].Peripheral_Name,l_a_st[k+1].Register_name)==0){
							printf("unsigned int dummy%d[%d];\n",l_dummy_u32,((Gen_Dummy(l_a_st[k].Offset,l_a_st[k+1].Offset)/4)-1));
							fprintf(l_out_ptr,"unsigned int dummy%d[%d];\n",l_dummy_u32++,((Gen_Dummy(l_a_st[k].Offset,l_a_st[k+1].Offset)/4)-1));
						}
					}
				}
	
			}
			
			printf("}%s_Type;\n",l_a2_st[l_h_u32].Peripheral_Name);
			printf("#define %s_BASE_ADDRS (%s)\n",l_a2_st[l_h_u32].Peripheral_Name,l_a2_st[l_h_u32].Base_Address);
			printf("#define %s ((%s_Type*)%s_BASE_ADDRS)\n",l_a2_st[l_h_u32].Peripheral_Name,l_a2_st[l_h_u32].Peripheral_Name,l_a2_st[l_h_u32].Peripheral_Name);
			printf("#endif  /* #if !defined(S32K144_REGISTER_H_) */\n");
			fprintf(l_out_ptr,"}%s_Type;\n",l_a2_st[l_h_u32].Peripheral_Name);
			fprintf(l_out_ptr,"#define %s_BASE_ADDRS (%s)\n",l_a2_st[l_h_u32].Peripheral_Name,l_a2_st[l_h_u32].Base_Address);
			fprintf(l_out_ptr,"#define %s ((%s_Type*)%s_BASE_ADDRS)\n",l_a2_st[l_h_u32].Peripheral_Name,l_a2_st[l_h_u32].Peripheral_Name,l_a2_st[l_h_u32].Peripheral_Name);
			fprintf(l_out_ptr,"#endif  /* #if !defined(S32K144_REGISTER_H_) */\n");
	
			fclose(l_template_ptr);
			fclose(l_in_ptr);
    		fclose(l_out_ptr);
		}
		
		else if(l_choose_u32==3){
			printf("Exit program !!!");
			break;
		}
		
		else{
			printf("Invalid number!\n");
			break;
		}
	}
	return 0;
}