#ifndef GLB_WARNING_H
#define GLB_WARNING_H

#include <QtCore>
#define G_WARN_MAX_COUNT 130
enum{

    G_WARN_NO_WARNING                      = 0x00        //无报警
,		G_WARN_P_CODE_ASYSTOLE				=0x1 			// * * *心脏停搏	超过4秒钟无心跳信号	高
,		G_WARN_P_CODE_APNEA						=0x2 			// * * *呼吸窒息	超过设定的呼吸窒息时间无呼吸信号	高
,		G_WARN_P_CODE_NOPULSE				=0x3 			// * * *无脉搏	超过15秒无脉搏信号	高
,		G_WARN_P_CODE_HRHIGH					=0x4 			// * * 心率太高	心率超过报警高限	高
,		G_WARN_P_CODE_HRLOW					=0x5 			// * * 心率太低	心率低于报警低限	高
,		G_WARN_P_CODE_ST1HIGH					=0x6 			// * * ST-I太高	I导联ST值超过报警高限	高
,		G_WARN_P_CODE_ST1LOW					=0x7 			// * * ST-I太低	I导联ST值低于报警低限	高
,		G_WARN_P_CODE_ST2HIGH					=0x8 			// * * ST-II太高	II导联ST值超过报警高限	高
,		G_WARN_P_CODE_ST2LOW					=0x9 			// * * ST-II太低	II导联ST值低于报警低限	高
,		G_WARN_P_CODE_ST3HIGH					=0xA 			// * * ST-III太高	III导联ST值超过报警高限	高
,		G_WARN_P_CODE_ST3LOW					=0xB 			// * * ST-III太低	III导联ST值低于报警低限	高
,		G_WARN_P_CODE_STAVRHIGH	  		=0xC 			// * * ST-AVR太高	AVR导联ST值超过报警高限	高
,		G_WARN_P_CODE_STAVRLOW	  		=0xD 			// * * ST-AVR太低	AVR导联ST值低于报警低限	高
,		G_WARN_P_CODE_STAVLHIGH	  		=0xE 			// * * ST-AVL太高	AVL导联ST值超过报警高限	高
,		G_WARN_P_CODE_STAVLLOW	  		=0xF 			// * * ST-AVL太低	AVL导联ST值低于报警低限	高
,		G_WARN_P_CODE_STAVFHIGH				=0x10			// * * ST-AVF太高	AVF导联ST值超过报警高限	高
,		G_WARN_P_CODE_STAVFLOW	  		=0x11			// * * ST-AVF太低	AVF导联ST值低于报警低限	高
,		G_WARN_P_CODE_STVHIGH	    		=0x12			// * * ST-V太高	V导联ST值超过报警高限	高
,		G_WARN_P_CODE_STVLOW		  		=0x13			// * * ST-V太低	V导联ST值低于报警低限	高
,		G_WARN_P_CODE_PVCHIGH	    		=0x14			// * * PVCs太高	PVCs值超过报警高限	高
,		G_WARN_P_CODE_SPO2HIGH	  		=0x15			// * * 氧饱和度太高	氧饱和度超过报警高限	中
,		G_WARN_P_CODE_SPO2LOW		  		=0x16			// * * 氧饱和度太低	氧饱和度低于报警低限	中
,		G_WARN_P_CODE_PRHIGH		  		=0x17			// * * 脉率太高	脉率超过报警高限	中
,		G_WARN_P_CODE_PRLOW			  		=0x18			// * * 脉率太低	脉率低于报警低限	中
,		G_WARN_P_CODE_NSHIGH					=0x19			// * * 收缩压太高	收缩压超过报警高限	中
,		G_WARN_P_CODE_NSLOW						=0x1A			// * * 收缩压太低	收缩压低于报警低限	中
,		G_WARN_P_CODE_NMHIGH					=0x1B			// * * 平均压太高	平均压超过报警高限	中
,		G_WARN_P_CODE_NMLOW						=0x1C			// * * 平均压太低	平均压低于报警低限	中
,		G_WARN_P_CODE_NDHIGH					=0x1D			// * * 舒张压太高	舒张压超过报警高限	中
,		G_WARN_P_CODE_NDLOW						=0x1E			// * * 舒张压太低	舒张压低于报警低限	中
,		G_WARN_P_CODE_RRHIGH					=0x1F			// * * 呼吸率太高	呼吸率超过报警高限	中
,		G_WARN_P_CODE_RRLOW						=0x20			// * * 呼吸率太低	呼吸率低于报警低限	中
,		G_WARN_P_CODE_TEMP1HIGH	  		=0x21			// * * 体温通道1太高	体温通道1超过报警高限	中
,		G_WARN_P_CODE_TEMP1LOW	  		=0x22			// * * 体温通道1太低	体温通道1低于报警低限	中
,		G_WARN_P_CODE_TEMP2HIGH	  		=0x23			// * * 体温通道2太高	体温通道2超过报警高限	中
,		G_WARN_P_CODE_TEMP2LOW	  		=0x24			// * * 体温通道2太低	体温通道2低于报警低限	中
,		G_WARN_P_CODE_IBP1NSHIGH	        		=0x25			// * * 主动脉压收缩压太高	主动脉收缩压超过报警高限	中
,		G_WARN_P_CODE_IBP1NSLOW	        		=0x26			// * * 主动脉压收缩压太低	主动脉收缩压低于报警低限	中
,		G_WARN_P_CODE_IBP1NMHIGH	        		=0x27			// * * 主动脉压平均压太高	主动脉平均压超过报警高限	中
,		G_WARN_P_CODE_IBP1NMLOW		        		=0x28			// * * 主动脉压平均压太低	主动脉平均压低于报警低限	中
,		G_WARN_P_CODE_IBP1NDHIGH	        		=0x29			// * * 主动脉压舒张压太高	主动脉舒张压超过报警高限	中
,		G_WARN_P_CODE_IBP1NDLOW	        		=0x2A			// * * 肺动脉压舒张压太低	肺动脉舒张压低于报警低限	中
,		G_WARN_P_CODE_IBP2NSHIGH	        		=0x2B			// * * 肺动脉压收缩压太高	肺动脉收缩压超过报警高限	中
,		G_WARN_P_CODE_IBP2NSLOW		        		=0x2C			// * * 肺动脉压收缩压太低	肺动脉收缩压低于报警低限	中
,		G_WARN_P_CODE_IBP2NMHIGH	        		=0x2D			// * * 肺动脉压平均压太高	肺动脉平均压超过报警高限	中
,		G_WARN_P_CODE_IBP2NMLOW	        		=0x2E			// * * 肺动脉压平均压太低	肺动脉平均压低于报警低限	中
,		G_WARN_P_CODE_IBP2NDHIGH	        		=0x2F			// * * 肺动脉压舒张压太高	肺动脉舒张压超过报警高限	中
,		G_WARN_P_CODE_IBP2NDLOW	        		=0x30			// * * 肺动脉压舒张压太低	肺动脉舒张压低于报警低限	中
,		G_WARN_P_CODE_IBP3NSHIGH	        		=0x31			// * * 中心静脉压收缩压太高	中心静脉收缩压超过报警高限	中
,		G_WARN_P_CODE_IBP3NSLOW	        		=0x32			// * * 中心静脉压收缩压太低	中心静脉收缩压低于报警低限	中
,		G_WARN_P_CODE_IBP3NMHIGH	        		=0x33			// * * 中心静脉压平均压太高	中心静脉平均压超过报警高限	中
,		G_WARN_P_CODE_IBP3NMLOW	        		=0x34			// * * 中心静脉压平均压太低	中心静脉平均压低于报警低限	中
,		G_WARN_P_CODE_IBP3NDHIGH	        		=0x35			// * * 中心静脉压舒张压太高	中心静脉舒张压超过报警高限	中
,		G_WARN_P_CODE_IBP3NDLOW	        		=0x36			// * * 中心静脉压舒张压太低	中心静脉舒张压低于报警低限	中
,		G_WARN_P_CODE_IBP4NSHIGH		        		=0x37			// * * 左房压收缩压太高	左房收缩压超过报警高限	中
,		G_WARN_P_CODE_IBP4NSLOW		        		=0x38			// * * 左房压收缩压太低	左房收缩压低于报警低限	中
,		G_WARN_P_CODE_IBP4NMHIGH	        		=0x39			// * * 左房压平均压太高	左房平均压超过报警高限	中
,		G_WARN_P_CODE_IBP4NMLOW		        		=0x3A			// * * 左房压平均压太低	左房平均压低于报警低限	中
,		G_WARN_P_CODE_IBP4NDHIGH		        		=0x3B			// * * 左房压舒张压太高	左房舒张压超过报警高限	中
,		G_WARN_P_CODE_IBP4NDLOW		        		=0x3C			// * * 左房压舒张压太低	左房舒张压低于报警低限	中
,		G_WARN_P_CODE_IBP5NSHIGH		        		=0x3D			// * * 右房压收缩压太高	右房收缩压超过报警高限	中
,		G_WARN_P_CODE_IBP5NSLOW		        		=0x3E			// * * 右房压收缩压太低	右房收缩压低于报警低限	中
,		G_WARN_P_CODE_IBP5NMHIGH		        		=0x3F			// * * 右房压平均压太高	右房平均压超过报警高限	中
,		G_WARN_P_CODE_IBP5NMLOW		        		=0x40			// * * 右房压平均压太低	右房平均压低于报警低限	中
,		G_WARN_P_CODE_IBP5NDHIGH		        		=0x41			// * * 右房压舒张压太高	右房舒张压超过报警高限	中
,		G_WARN_P_CODE_IBP5NDLOW		        		=0x42			// * * 右房压舒张压太低	右房舒张压低于报警低限	中
,		G_WARN_P_CODE_IBP6NSHIGH		        		=0x43			// * * 颅内压收缩压太高	颅内收缩压超过报警高限	中
,		G_WARN_P_CODE_IBP6NSLOW		        		=0x44			// * * 颅内压收缩压太低	颅内收缩压低于报警低限	中
,		G_WARN_P_CODE_IBP6NMHIGH		        		=0x45			// * * 颅内压平均压太高	颅内平均压超过报警高限	中
,		G_WARN_P_CODE_IBP6NMLOW		        		=0x46			// * * 颅内压平均压太低	颅内平均压低于报警低限	高
,		G_WARN_P_CODE_IBP6NDHIGH		        		=0x47			// * * 颅内压舒张压太高	颅内舒张压超过报警高限	高
,		G_WARN_P_CODE_IBP6NDLOW		        		=0x48			// * * 颅内压舒张压太低	颅内舒张压低于报警低限	高
,		G_WARN_P_CODE_IBP7NSHIGH		        		=0x49			// * * P1压太高	P1收缩压超过报警高限	高
,		G_WARN_P_CODE_IBP7NSLOW		        		=0x4A			// * * P1压太低	P1收缩压低于报警低限	高
,		G_WARN_P_CODE_IBP7NMHIGH		        		=0x4B			// * * P1平均压太高	P1平均压超过报警高限	高
,		G_WARN_P_CODE_IBP7NMLOW		        		=0x4C			// * * P1平均压太低	P1平均压低于报警低限	高
,		G_WARN_P_CODE_IBP7NDHIGH		        		=0x4D			// * * P1舒张压太高	P1舒张压超过报警高限	高
,		G_WARN_P_CODE_IBP7NDLOW		        		=0x4E			// * * P1舒张压太低	P1舒张压低于报警低限	高
,		G_WARN_P_CODE_IBP8NSHIGH		        		=0x4F			// * * P2压太高	P2收缩压超过报警高限	高
,		G_WARN_P_CODE_IBP8NSLOW		        		=0x50			// * * P2压太低	P2收缩压低于报警低限	高
,		G_WARN_P_CODE_IBP8NMHIGH		        		=0x51			// * * P2平均压太高	P2平均压超过报警高限	高
,		G_WARN_P_CODE_IBP8NMLOW		        		=0x52			// * * P2平均压太低	P2平均压低于报警低限	高
,		G_WARN_P_CODE_IBP8NDHIGH		        		=0x53			// * * P2舒张压太高	P2舒张压超过报警高限	高
,		G_WARN_P_CODE_IBP8NDLOW		        		=0x54			// * * P2舒张压太低	P2舒张压低于报警低限	高
,		G_WARN_P_CODE_ETCO2HIGH	//=0x55			// * * 呼末CO₂太高	呼末CO₂超过报警高限	中
,		G_WARN_P_CODE_ETCO2LOW  	//=0x56			// * * 呼末CO₂太低	呼末CO₂低于报警低限	中
,		G_WARN_P_CODE_FICO2HIGH		        		=0x57			// * * 吸末CO₂太高	吸末CO₂超过报警高限	中
,		G_WARN_P_CODE_FICO2LOW		        		=0x58			// * * 吸末CO₂太低	吸末CO₂低于报警低限	中
,		G_WARN_P_CODE_SPHIGH	        		//=0x59			// * * 气道呼吸率太高	气道呼吸率超过报警高限	中
,		G_WARN_P_CODE_SPLOW	        		//=0x5A  		// * * 气道呼吸率太低	气道呼吸率低于报警低限	中


//		报警信息	触发条件		报警优先级
,		G_WARN_T_CODE_ECGLEADOFF			  		//=0x81			// * * 心电导联脱落	RL或2个以上的心电导联脱落		低
,		G_WARN_T_CODE_RALEADOFF						//=0x82			// * * 心电导联RA脱落	RA导联脱落		低
,		G_WARN_T_CODE_LALEADOFF						//=0x83			// * * 心电导联LA脱落	LA导联脱落		低
,		G_WARN_T_CODE_LLLEADOFF						//=0x84			// * * 心电导联LL脱落	LL导联脱落		低
,		G_WARN_T_CODE_VLEADOFF				  		//=0x85			// * * 心电导联V脱落	V导联脱落		低
,		G_WARN_T_CODE_MODUINITERR				//			  		=0x86			// * * 模块初始化错	模块自检错误		低
,		G_WARN_T_CODE_COMMSTOP				  	//	=0x87			// * * *模块通讯停止	模块和主机通讯出现问题		低
,		G_WARN_T_CODE_COMMERR						//	=0x88			// * * 模块通讯错	模块和主机通讯出现问题		低
,		G_WARN_T_CODE_WARNLIMITERR								  //		=0x89			// * * 参数报警限错	参数的报警限被意外改动		低
,		G_WARN_T_CODE_PARALIMITERR								 // 		=0x8A			// * * 测量范围超界	参数的测量值超出了系统所能进行的测量范围		低
,		G_WARN_T_CODE_SPO2SENSER			  		//=0x8B			// * * 血氧探头脱落	血氧探头未接好		低
,		G_WARN_T_CODE_SPO2FINGER			  		//=0x8C			// * * 血氧探头手指脱落	手指从血氧探头中脱落		低
,		G_WARN_T_CODE_SEARCHPULSE					//		  		=0x8D			// * * 搜索脉搏...	血氧探头没有连接好或病人运动手臂		低
,		G_WARN_T_CODE_TEMP1SENSOR					//=0x8E			// * * 体温通道1探头脱落	体温通道1探头未接好		低
,		G_WARN_T_CODE_TEMP2SENSOR					//=0x8F			// * * 体温通道2探头脱落	体温通道2探头未接好		低
,		G_WARN_T_CODE_WATCHDOGERR						//	  		=0x90			// * * 看门狗错误	主机看门狗自检失败		低
,		G_WARN_T_CODE_SYSTIMEERR							//	  		=0x91			// * * 系统时间丢失	系统时钟未设置		低
,		G_WARN_T_CODE_12VHIGH							  		//=0x92			// * * 12V电压太高	12V电压检测超出正常电压范围		低
,		G_WARN_T_CODE_12VLOW							  		//=0x93			// * * 12V电压太低	12V电压检测低于正常电压范围		低
,		G_WARN_T_CODE_3_3VHIGH							  	//	=0x94			// * * 3.3V电压太高	3.3V电压检测超出正常电压范围		低
,		G_WARN_T_CODE_3_3VLOW							  		//=0x95			// * * 3.3V电压太低	3.3V电压检测低于正常电压范围		低
,		G_WARN_T_CODE_BATHIGH							  		//=0x96			// * * 电池电压太高	电池电压检测超出正常电压范围		低
,		G_WARN_T_CODE_BATLOW							  		//=0x97			// * * 电池不足，请立即充电	电池电量不足		低
,		G_WARN_T_CODE_TIELOOSE							  	//	=0x98			// * 无创血压袖带松	袖带未连接好		低
,		G_WARN_T_CODE_NBPLEAK							//=0x99			// * 无创血压漏气	袖带未连接好或气路漏气		低
,		G_WARN_T_CODE_NBPAIRERR						//=0x9A			// * 无创血压放气错误	血压测量时放气出现问题		低
,		G_WARN_T_CODE_NBPWEAK						//	=0x9B			// * 无创血压信号太弱	血压测量时脉搏信号太弱，无法计算出血压		低
,		G_WARN_T_CODE_NBPEXD					  		//=0x9C			// * 无创血压测量超界	血压测量时血压或脉搏信号超出正常范围，无法进行测量		低
,		G_WARN_T_CODE_NBPMOVE						//	=0x9D			// * 无创血压手臂运动	病人手臂运动		低
,		G_WARN_T_CODE_NBPOVERPRESSURE		//	=0x9E			// * * 无创血压过压	压力值超过测量范围		低
,		G_WARN_T_CODE_NBPSAT					  		//=0x9F			// * 无创血压信号饱和	血压测量时脉搏信号超出正常范围，无法进行测量		低
,		G_WARN_T_CODE_NBPLEAKCKFAIL				//			  		=0xA0			// * 无创血压漏气检测失败	袖带未连接好或气路漏气		低
,		G_WARN_T_CODE_NBPFAIL							//=0xA1			// * * 无创血压系统错误	血压系统自检失败，一般是压力传感器实效导致自检失败		低
,		G_WARN_T_CODE_NBPTIMEOUT			  		//=0xA2			// * * 无创血压测量超时	血压测量超时		低
,		G_WARN_T_CODE_NBPTIEERR						//	  		=0xA3			// * * 无创血压袖带类型错	病人类型为成人时使用了新生儿袖带		低
,		G_WARN_T_CODE_NBPMESSUREFAIL		  	//	=0xA4			// * * 无创血压测量失败	本次血压测量未能计算出血压		低
,		G_WARN_T_CODE_NBPRESETERR					//		  		=0xA5			// * * 无创血压非法复位	血压测量时异常复位		低
,		G_WARN_T_CODE_CO2STANDBY					//			  		=0xA6			// * * CO₂待命	CO₂处于待命状态		低
,		G_WARN_T_CODE_CO2STOP						//	  		=0xA7			// * * *CO₂通讯停止	CO₂模块和主机通讯出现问题		低


    ,       G_WARN_T_CODE_HEARTV                              //心跳音
,     G_WARN_BAD_WARNING                     //  =0xff      //预留，错误报警
};
//报警信息	触发条件	报警优先级
/*
#define     G_WARN_BAD_WARNING                       0xff      //预留，错误报警
#define     G_WARN_NO_WARNING                       0x00        //无报警
#define		G_WARN_P_CODE_ASYSTOLE				0x1 			// * * *心脏停搏	超过4秒钟无心跳信号	高
#define		G_WARN_P_CODE_APNEA						0x2 			// * * *呼吸窒息	超过设定的呼吸窒息时间无呼吸信号	高
#define		G_WARN_P_CODE_NOPULSE				0x3 			// * * *无脉搏	超过15秒无脉搏信号	高
#define		G_WARN_P_CODE_HRHIGH					0x4 			// * * 心率太高	心率超过报警高限	高
#define		G_WARN_P_CODE_HRLOW					0x5 			// * * 心率太低	心率低于报警低限	高
#define		G_WARN_P_CODE_ST1HIGH					0x6 			// * * ST-I太高	I导联ST值超过报警高限	高
#define		G_WARN_P_CODE_ST1LOW					0x7 			// * * ST-I太低	I导联ST值低于报警低限	高
#define		G_WARN_P_CODE_ST2HIGH					0x8 			// * * ST-II太高	II导联ST值超过报警高限	高
#define		G_WARN_P_CODE_ST2LOW					0x9 			// * * ST-II太低	II导联ST值低于报警低限	高
#define		G_WARN_P_CODE_ST3HIGH					0xA 			// * * ST-III太高	III导联ST值超过报警高限	高
#define		G_WARN_P_CODE_ST3LOW					0xB 			// * * ST-III太低	III导联ST值低于报警低限	高
#define		G_WARN_P_CODE_STAVRHIGH	  		0xC 			// * * ST-AVR太高	AVR导联ST值超过报警高限	高
#define		G_WARN_P_CODE_STAVRLOW	  		0xD 			// * * ST-AVR太低	AVR导联ST值低于报警低限	高
#define		G_WARN_P_CODE_STAVLHIGH	  		0xE 			// * * ST-AVL太高	AVL导联ST值超过报警高限	高
#define		G_WARN_P_CODE_STAVLLOW	  		0xF 			// * * ST-AVL太低	AVL导联ST值低于报警低限	高
#define		G_WARN_P_CODE_STAVFHIGH				0x10			// * * ST-AVF太高	AVF导联ST值超过报警高限	高
#define		G_WARN_P_CODE_STAVFLOW	  		0x11			// * * ST-AVF太低	AVF导联ST值低于报警低限	高
#define		G_WARN_P_CODE_STVHIGH	    		0x12			// * * ST-V太高	V导联ST值超过报警高限	高
#define		G_WARN_P_CODE_STVLOW		  		0x13			// * * ST-V太低	V导联ST值低于报警低限	高
#define		G_WARN_P_CODE_PVCHIGH	    		0x14			// * * PVCs太高	PVCs值超过报警高限	高
#define		G_WARN_P_CODE_SPO2HIGH	  		0x15			// * * 氧饱和度太高	氧饱和度超过报警高限	中
#define		G_WARN_P_CODE_SPO2LOW		  		0x16			// * * 氧饱和度太低	氧饱和度低于报警低限	中
#define		G_WARN_P_CODE_PRHIGH		  		0x17			// * * 脉率太高	脉率超过报警高限	中
#define		G_WARN_P_CODE_PRLOW			  		0x18			// * * 脉率太低	脉率低于报警低限	中
#define		G_WARN_P_CODE_NSHIGH					0x19			// * * 收缩压太高	收缩压超过报警高限	中
#define		G_WARN_P_CODE_NSLOW						0x1A			// * * 收缩压太低	收缩压低于报警低限	中
#define		G_WARN_P_CODE_NMHIGH					0x1B			// * * 平均压太高	平均压超过报警高限	中
#define		G_WARN_P_CODE_NMLOW						0x1C			// * * 平均压太低	平均压低于报警低限	中
#define		G_WARN_P_CODE_NDHIGH					0x1D			// * * 舒张压太高	舒张压超过报警高限	中
#define		G_WARN_P_CODE_NDLOW						0x1E			// * * 舒张压太低	舒张压低于报警低限	中
#define		G_WARN_P_CODE_RRHIGH					0x1F			// * * 呼吸率太高	呼吸率超过报警高限	中
#define		G_WARN_P_CODE_RRLOW						0x20			// * * 呼吸率太低	呼吸率低于报警低限	中
#define		G_WARN_P_CODE_TEMP1HIGH	  		0x21			// * * 体温通道1太高	体温通道1超过报警高限	中
#define		G_WARN_P_CODE_TEMP1LOW	  		0x22			// * * 体温通道1太低	体温通道1低于报警低限	中
#define		G_WARN_P_CODE_TEMP2HIGH	  		0x23			// * * 体温通道2太高	体温通道2超过报警高限	中
#define		G_WARN_P_CODE_TEMP2LOW	  		0x24			// * * 体温通道2太低	体温通道2低于报警低限	中
#define		G_WARN_P_CODE_IBP1NSHIGH	        		0x25			// * * 主动脉压收缩压太高	主动脉收缩压超过报警高限	中
#define		G_WARN_P_CODE_IBP1NSLOW	        		0x26			// * * 主动脉压收缩压太低	主动脉收缩压低于报警低限	中
#define		G_WARN_P_CODE_IBP1NMHIGH	        		0x27			// * * 主动脉压平均压太高	主动脉平均压超过报警高限	中
#define		G_WARN_P_CODE_IBP1NMLOW		        		0x28			// * * 主动脉压平均压太低	主动脉平均压低于报警低限	中
#define		G_WARN_P_CODE_IBP1NDHIGH	        		0x29			// * * 主动脉压舒张压太高	主动脉舒张压超过报警高限	中
#define		G_WARN_P_CODE_IBP1NDLOW	        		0x2A			// * * 肺动脉压舒张压太低	肺动脉舒张压低于报警低限	中
#define		G_WARN_P_CODE_IBP2NSHIGH	        		0x2B			// * * 肺动脉压收缩压太高	肺动脉收缩压超过报警高限	中
#define		G_WARN_P_CODE_IBP2NSLOW		        		0x2C			// * * 肺动脉压收缩压太低	肺动脉收缩压低于报警低限	中
#define		G_WARN_P_CODE_IBP2NMHIGH	        		0x2D			// * * 肺动脉压平均压太高	肺动脉平均压超过报警高限	中
#define		G_WARN_P_CODE_IBP2NMLOW	        		0x2E			// * * 肺动脉压平均压太低	肺动脉平均压低于报警低限	中
#define		G_WARN_P_CODE_IBP2NDHIGH	        		0x2F			// * * 肺动脉压舒张压太高	肺动脉舒张压超过报警高限	中
#define		G_WARN_P_CODE_IBP2NDLOW	        		0x30			// * * 肺动脉压舒张压太低	肺动脉舒张压低于报警低限	中
#define		G_WARN_P_CODE_IBP3NSHIGH	        		0x32			// * * 中心静脉压收缩压太高	中心静脉收缩压超过报警高限	中
#define		G_WARN_P_CODE_IBP3NSLOW	        		0x33			// * * 中心静脉压收缩压太低	中心静脉收缩压低于报警低限	中
#define		G_WARN_P_CODE_IBP3NMHIGH	        		0x34			// * * 中心静脉压平均压太高	中心静脉平均压超过报警高限	中
#define		G_WARN_P_CODE_IBP3NMLOW	        		0x35			// * * 中心静脉压平均压太低	中心静脉平均压低于报警低限	中
#define		G_WARN_P_CODE_IBP3NDHIGH	        		0x36			// * * 中心静脉压舒张压太高	中心静脉舒张压超过报警高限	中
#define		G_WARN_P_CODE_IBP3NDLOW	        		0x37			// * * 中心静脉压舒张压太低	中心静脉舒张压低于报警低限	中
//#define		G_WARN_P_CODE_		        		0x38			// * * 左房压收缩压太高	左房收缩压超过报警高限	中
//#define		G_WARN_P_CODE_		        		0x39			// * * 左房压收缩压太低	左房收缩压低于报警低限	中
//#define		G_WARN_P_CODE_		        		0x3A			// * * 左房压平均压太高	左房平均压超过报警高限	中
//#define		G_WARN_P_CODE_		        		0x3B			// * * 左房压平均压太低	左房平均压低于报警低限	中
//#define		G_WARN_P_CODE_		        		0x3C			// * * 左房压舒张压太高	左房舒张压超过报警高限	中
//#define		G_WARN_P_CODE_		        		0x3D			// * * 左房压舒张压太低	左房舒张压低于报警低限	中
//#define		G_WARN_P_CODE_		        		0x3E			// * * 右房压收缩压太高	右房收缩压超过报警高限	中
//#define		G_WARN_P_CODE_		        		0x3F			// * * 右房压收缩压太低	右房收缩压低于报警低限	中
//#define		G_WARN_P_CODE_		        		0x40			// * * 右房压平均压太高	右房平均压超过报警高限	中
//#define		G_WARN_P_CODE_		        		0x41			// * * 右房压平均压太低	右房平均压低于报警低限	中
//#define		G_WARN_P_CODE_		        		0x42			// * * 右房压舒张压太高	右房舒张压超过报警高限	中
//#define		G_WARN_P_CODE_		        		0x43			// * * 右房压舒张压太低	右房舒张压低于报警低限	中
//#define		G_WARN_P_CODE_		        		0x44			// * * 颅内压收缩压太高	颅内收缩压超过报警高限	中
//#define		G_WARN_P_CODE_		        		0x45			// * * 颅内压收缩压太低	颅内收缩压低于报警低限	中
//#define		G_WARN_P_CODE_		        		0x46			// * * 颅内压平均压太高	颅内平均压超过报警高限	中
//#define		G_WARN_P_CODE_		        		0x47			// * * 颅内压平均压太低	颅内平均压低于报警低限	高
//#define		G_WARN_P_CODE_		        		0x48			// * * 颅内压舒张压太高	颅内舒张压超过报警高限	高
//#define		G_WARN_P_CODE_		        		0x49			// * * 颅内压舒张压太低	颅内舒张压低于报警低限	高
//#define		G_WARN_P_CODE_		        		0x4A			// * * P1压太高	P1收缩压超过报警高限	高
//#define		G_WARN_P_CODE_		        		0x4B			// * * P1压太低	P1收缩压低于报警低限	高
//#define		G_WARN_P_CODE_		        		0x4C			// * * P1平均压太高	P1平均压超过报警高限	高
//#define		G_WARN_P_CODE_		        		0x4D			// * * P1平均压太低	P1平均压低于报警低限	高
//#define		G_WARN_P_CODE_		        		0x4E			// * * P1舒张压太高	P1舒张压超过报警高限	高
//#define		G_WARN_P_CODE_		        		0x4F			// * * P1舒张压太低	P1舒张压低于报警低限	高
//#define		G_WARN_P_CODE_		        		0x50			// * * P2压太高	P2收缩压超过报警高限	高
//#define		G_WARN_P_CODE_		        		0x51			// * * P2压太低	P2收缩压低于报警低限	高
//#define		G_WARN_P_CODE_		        		0x52			// * * P2平均压太高	P2平均压超过报警高限	高
//#define		G_WARN_P_CODE_		        		0x53			// * * P2平均压太低	P2平均压低于报警低限	高
//#define		G_WARN_P_CODE_		        		0x54			// * * P2舒张压太高	P2舒张压超过报警高限	高
//#define		G_WARN_P_CODE_		        		0x55			// * * P2舒张压太低	P2舒张压低于报警低限	高
#define		G_WARN_P_CODE_CO2HIGH	0x56			// * * 呼末CO₂太高	呼末CO₂超过报警高限	中
#define		G_WARN_P_CODE_CO2LOW  	0x57			// * * 呼末CO₂太低	呼末CO₂低于报警低限	中
//#define		G_WARN_P_CODE_		        		0x58			// * * 吸末CO₂太高	吸末CO₂超过报警高限	中
//#define		G_WARN_P_CODE_		        		0x59			// * * 吸末CO₂太低	吸末CO₂低于报警低限	中
#define		G_WARN_P_CODE_SPHIGH	        		0x5A			// * * 气道呼吸率太高	气道呼吸率超过报警高限	中
#define		G_WARN_P_CODE_SPLOW	        		0x5B  		// * * 气道呼吸率太低	气道呼吸率低于报警低限	中


//		报警信息	触发条件		报警优先级
#define		G_WARN_T_CODE_ECGLEADOFF			  		0x81			// * * 心电导联脱落	RL或2个以上的心电导联脱落		低
#define		G_WARN_T_CODE_RALEADOFF						0x82			// * * 心电导联RA脱落	RA导联脱落		低
#define		G_WARN_T_CODE_LALEADOFF						0x83			// * * 心电导联LA脱落	LA导联脱落		低
#define		G_WARN_T_CODE_LLLEADOFF						0x84			// * * 心电导联LL脱落	LL导联脱落		低
#define		G_WARN_T_CODE_VLEADOFF				  		0x85			// * * 心电导联V脱落	V导联脱落		低
#define		G_WARN_T_CODE_MODUINITERR							  		0x86			// * * 模块初始化错	模块自检错误		低
#define		G_WARN_T_CODE_COMMSTOP				  		0x87			// * * *模块通讯停止	模块和主机通讯出现问题		低
#define		G_WARN_T_CODE_COMMERR							0x88			// * * 模块通讯错	模块和主机通讯出现问题		低
//#define		G_WARN_T_CODE_								  		0x89			// * * 参数报警限错	参数的报警限被意外改动		低
//#define		G_WARN_T_CODE_								  		0x8A			// * * 测量范围超界	参数的测量值超出了系统所能进行的测量范围		低
#define		G_WARN_T_CODE_SPO2SENSER			  		0x8B			// * * 血氧探头脱落	血氧探头未接好		低
#define		G_WARN_T_CODE_SPO2FINGER			  		0x8C			// * * 血氧探头手指脱落	手指从血氧探头中脱落		低
#define		G_WARN_T_CODE_SEARCHPULSE							  		0x8D			// * * 搜索脉搏...	血氧探头没有连接好或病人运动手臂		低
#define		G_WARN_T_CODE_TEMP1SENSOR					0x8E			// * * 体温通道1探头脱落	体温通道1探头未接好		低
#define		G_WARN_T_CODE_TEMP2SENSOR					0x8F			// * * 体温通道2探头脱落	体温通道2探头未接好		低
#define		G_WARN_T_CODE_WATCHDOGERR							  		0x90			// * * 看门狗错误	主机看门狗自检失败		低
#define		G_WARN_T_CODE_SYSTIMEERR								  		0x91			// * * 系统时间丢失	系统时钟未设置		低
#define		G_WARN_T_CODE_12VHIGH							  		0x92			// * * 12V电压太高	12V电压检测超出正常电压范围		低
#define		G_WARN_T_CODE_12VLOW							  		0x93			// * * 12V电压太低	12V电压检测低于正常电压范围		低
#define		G_WARN_T_CODE_3_3VHIGH							  		0x94			// * * 3.3V电压太高	3.3V电压检测超出正常电压范围		低
#define		G_WARN_T_CODE_3_3VLOW							  		0x95			// * * 3.3V电压太低	3.3V电压检测低于正常电压范围		低
#define		G_WARN_T_CODE_BATHIGH							  		0x96			// * * 电池电压太高	电池电压检测超出正常电压范围		低
#define		G_WARN_T_CODE_BATLOW							  		0x97			// * * 电池不足，请立即充电	电池电量不足		低
#define		G_WARN_T_CODE_TIELOOSE							  		0x98			// * 无创血压袖带松	袖带未连接好		低
#define		G_WARN_T_CODE_NBPLEAK							0x99			// * 无创血压漏气	袖带未连接好或气路漏气		低
#define		G_WARN_T_CODE_NBPAIRERR						0x9A			// * 无创血压放气错误	血压测量时放气出现问题		低
#define		G_WARN_T_CODE_NBPWEAK							0x9B			// * 无创血压信号太弱	血压测量时脉搏信号太弱，无法计算出血压		低
#define		G_WARN_T_CODE_NBPEXD					  		0x9C			// * 无创血压测量超界	血压测量时血压或脉搏信号超出正常范围，无法进行测量		低
#define		G_WARN_T_CODE_NBPMOVE							0x9D			// * 无创血压手臂运动	病人手臂运动		低
#define		G_WARN_T_CODE_NBPOVERPRESSURE			0x9E			// * * 无创血压过压	压力值超过测量范围		低
#define		G_WARN_T_CODE_NBPSAT					  		0x9F			// * 无创血压信号饱和	血压测量时脉搏信号超出正常范围，无法进行测量		低
#define		G_WARN_T_CODE_NBPLEAKCKFAIL							  		0xA0			// * 无创血压漏气检测失败	袖带未连接好或气路漏气		低
#define		G_WARN_T_CODE_NBPFAIL							0xA1			// * * 无创血压系统错误	血压系统自检失败，一般是压力传感器实效导致自检失败		低
#define		G_WARN_T_CODE_NBPTIMEOUT			  		0xA2			// * * 无创血压测量超时	血压测量超时		低
#define		G_WARN_T_CODE_NBPTIEERR							  		0xA3			// * * 无创血压袖带类型错	病人类型为成人时使用了新生儿袖带		低
#define		G_WARN_T_CODE_NBPMESSUREFAIL		  		0xA4			// * * 无创血压测量失败	本次血压测量未能计算出血压		低
#define		G_WARN_T_CODE_NBPRESETERR							  		0xA5			// * * 无创血压非法复位	血压测量时异常复位		低
#define		G_WARN_T_CODE_CO2STANDBY								  		0xA6			// * * CO₂待命	CO₂处于待命状态		低
#define		G_WARN_T_CODE_CO2STOP							  		0xA7			// * * *CO₂通讯停止	CO₂模块和主机通讯出现问题		低

*/

//	报警信息	触发条件	报警优先级
#define		G_WARN_P_TXT_ASYSTOLE		"心脏停搏"     									//高	//超过4秒钟无心跳信号
#define		G_WARN_P_TXT_APNEA		"呼吸窒息"     									//高	//超过设定的呼吸窒息时间无呼吸信号
#define		G_WARN_P_TXT_NOPULSE		"无脉搏"     									//高	//超过15秒无脉搏信号
#define		G_WARN_P_TXT_HRHIGH		"心率太高"     									//高	//心率超过报警高限
#define		G_WARN_P_TXT_HRHLOW		"心率太低"      									//高	//心率低于报警低限
#define		G_WARN_P_TXT_ST1HIGH		"ST-I太高"    									//高	//I导联ST值超过报警高限
#define		G_WARN_P_TXT_ST1LOW		"ST-I太低"    									//高	//I导联ST值低于报警低限
#define		G_WARN_P_TXT_ST2HIGH		"ST-II太高"   									//高	//II导联ST值超过报警高限
#define		G_WARN_P_TXT_ST2LOW		"ST-II太低"   									//高	//II导联ST值低于报警低限
#define		G_WARN_P_TXT_ST3HIGH		"ST-III太高"  									//高	//III导联ST值超过报警高限
#define		G_WARN_P_TXT_ST3LOW		"ST-III太低"  									//高	//III导联ST值低于报警低限
#define		G_WARN_P_TXT_STAVRHIGH	"ST-AVR太高"  									//高	//AVR导联ST值超过报警高限
#define		G_WARN_P_TXT_STAVRLOW       "ST-AVR太低"  									//高	//AVR导联ST值低于报警低限
#define		G_WARN_P_TXT_STAVLHIGH		"ST-AVL太高"  									//高	//AVL导联ST值超过报警高限
#define		G_WARN_P_TXT_STAVLLOW		"ST-AVL太低"  									//高	//AVL导联ST值低于报警低限
#define		G_WARN_P_TXT_STAVFHIGH		"ST-AVF太高"  									//高	//AVF导联ST值超过报警高限
#define		G_WARN_P_TXT_STAVFLOW		"ST-AVF太低"  									//高	//AVF导联ST值低于报警低限
#define		G_WARN_P_TXT_STVHIGH		"ST-V太高"    									//高	//V导联ST值超过报警高限
#define		G_WARN_P_TXT_STVLOW		"ST-V太低"    									//高	//V导联ST值低于报警低限
#define		G_WARN_P_TXT_PVCHIGH		"PVCs太高"    									//高	//PVCs值超过报警高限
#define		G_WARN_P_TXT_SPO2HIGH		"氧饱和度太高"    									//中	//氧饱和度超过报警高限
#define		G_WARN_P_TXT_SPO2LOW		"氧饱和度太低"    									//中	//氧饱和度低于报警低限
#define		G_WARN_P_TXT_PRHIGH		"脉率太高"      									//中	//脉率超过报警高限
#define		G_WARN_P_TXT_PRLOW		"脉率太低"      									//中	//脉率低于报警低限
#define		G_WARN_P_TXT_NSHIGH		"收缩压太高"     									//中	//收缩压超过报警高限
#define		G_WARN_P_TXT_NSLOW		"收缩压太低"     									//中	//收缩压低于报警低限
#define		G_WARN_P_TXT_NMHIGH		"平均压太高"     									//中	//平均压超过报警高限
#define		G_WARN_P_TXT_NMLOW		"平均压太低"     									//中	//平均压低于报警低限
#define		G_WARN_P_TXT_NDHIGH		"舒张压太高"     									//中	//舒张压超过报警高限
#define		G_WARN_P_TXT_NDLOW		"舒张压太低"     									//中	//舒张压低于报警低限
#define		G_WARN_P_TXT_RRHIGH		"呼吸率太高"     									//中	//呼吸率超过报警高限
#define		G_WARN_P_TXT_RRLOW		"呼吸率太低"     									//中	//呼吸率低于报警低限
#define		G_WARN_P_TXT_TEMP1HIGH		"体温通道1太高"   									//中	//体温通道1超过报警高限
#define		G_WARN_P_TXT_TEMP1LOW		"体温通道1太低"   									//中	//体温通道1低于报警低限
#define		G_WARN_P_TXT_TEMP2HIGH		"体温通道2太高"   									//中	//体温通道2超过报警高限
#define		G_WARN_P_TXT_TEMP2LOW		"体温通道2太低"   									//中	//体温通道2低于报警低限
#define		G_WARN_P_TXT_IBP1NSHIGH		"主动脉压收缩压太高" 									//中	//主动脉收缩压超过报警高限
#define		G_WARN_P_TXT_IBP1NSLOW		"主动脉压收缩压太低" 									//中	//主动脉收缩压低于报警低限
#define		G_WARN_P_TXT_IBP1NMHIGH		"主动脉压平均压太高" 									//中	//主动脉平均压超过报警高限
#define		G_WARN_P_TXT_IBP1NMLOW		"主动脉压平均压太低" 									//中	//主动脉平均压低于报警低限
#define		G_WARN_P_TXT_IBP1NDHIGH		"主动脉压舒张压太高" 									//中	//主动脉舒张压超过报警高限
#define		G_WARN_P_TXT_IBP1NDLOW		"肺动脉压舒张压太低" 									//中	//肺动脉舒张压低于报警低限
#define		G_WARN_P_TXT_IBP2NSHIGH		"肺动脉压收缩压太高" 									//中	//肺动脉收缩压超过报警高限
#define		G_WARN_P_TXT_IBP2NSLOW		"肺动脉压收缩压太低" 									//中	//肺动脉收缩压低于报警低限
#define		G_WARN_P_TXT_IBP2NMHIGH		"肺动脉压平均压太高" 									//中	//肺动脉平均压超过报警高限
#define		G_WARN_P_TXT_IBP2NMLOW		"肺动脉压平均压太低" 									//中	//肺动脉平均压低于报警低限
#define		G_WARN_P_TXT_IBP2NDHIGH		"肺动脉压舒张压太高" 									//中	//肺动脉舒张压超过报警高限
#define		G_WARN_P_TXT_IBP2NDLOW		"肺动脉压舒张压太低" 									//中	//肺动脉舒张压低于报警低限
#define		G_WARN_P_TXT_IBP3NSHIGH		"中心静脉压收缩压太高"									//中	//中心静脉收缩压超过报警高限
#define		G_WARN_P_TXT_IBP3NSLOW		"中心静脉压收缩压太低"									//中	//中心静脉收缩压低于报警低限
#define		G_WARN_P_TXT_IBP3NMHIGH		"中心静脉压平均压太高"									//中	//中心静脉平均压超过报警高限
#define		G_WARN_P_TXT_IBP3NMLOW		"中心静脉压平均压太低"									//中	//中心静脉平均压低于报警低限
#define		G_WARN_P_TXT_IBP3NDHIGH		"中心静脉压舒张压太高"									//中	//中心静脉舒张压超过报警高限
#define		G_WARN_P_TXT_IBP3NDLOW		"中心静脉压舒张压太低"									//中	//中心静脉舒张压低于报警低限
#define		G_WARN_P_TXT_IBP4NSHIGH		"左房压收缩压太高"  									//中	//左房收缩压超过报警高限
#define		G_WARN_P_TXT_IBP4NSLOW		"左房压收缩压太低"  									//中	//左房收缩压低于报警低限
#define		G_WARN_P_TXT_IBP4NMHIGH		"左房压平均压太高"  									//中	//左房平均压超过报警高限
#define		G_WARN_P_TXT_IBP4NMLOW		"左房压平均压太低"  									//中	//左房平均压低于报警低限
#define		G_WARN_P_TXT_IBP4NDHIGH		"左房压舒张压太高"  									//中	//左房舒张压超过报警高限
#define		G_WARN_P_TXT_IBP4NDLOW		"左房压舒张压太低"  									//中	//左房舒张压低于报警低限
#define		G_WARN_P_TXT_IBP5NSHIGH		"右房压收缩压太高"  									//中	//右房收缩压超过报警高限
#define		G_WARN_P_TXT_IBP5NSLOW		"右房压收缩压太低"  									//中	//右房收缩压低于报警低限
#define		G_WARN_P_TXT_IBP5NMHIGH		"右房压平均压太高"  									//中	//右房平均压超过报警高限
#define		G_WARN_P_TXT_IBP5NMLOW		"右房压平均压太低"  									//中	//右房平均压低于报警低限
#define		G_WARN_P_TXT_IBP5NDHIGH		"右房压舒张压太高"  									//中	//右房舒张压超过报警高限
#define		G_WARN_P_TXT_IBP5NDLOW		"右房压舒张压太低"  									//中	//右房舒张压低于报警低限
#define		G_WARN_P_TXT_IBP6NSHIGH		"颅内压收缩压太高"  									//中	//颅内收缩压超过报警高限
#define		G_WARN_P_TXT_IBP6NSLOW		"颅内压收缩压太低"  									//中	//颅内收缩压低于报警低限
#define		G_WARN_P_TXT_IBP6NMHIGH		"颅内压平均压太高"  									//中	//颅内平均压超过报警高限
#define		G_WARN_P_TXT_IBP6NMLOW		"颅内压平均压太低"  									//高	//颅内平均压低于报警低限
#define		G_WARN_P_TXT_IBP6NDHIGH		"颅内压舒张压太高"  									//高	//颅内舒张压超过报警高限
#define		G_WARN_P_TXT_IBP6NDLOW		"颅内压舒张压太低"  									//高	//颅内舒张压低于报警低限
#define		G_WARN_P_TXT_IBP7NSHIGH		"P1压太高"    									//高	//P1收缩压超过报警高限
#define		G_WARN_P_TXT_IBP7NSLOW		"P1压太低"    									//高	//P1收缩压低于报警低限
#define		G_WARN_P_TXT_IBP7NMHIGH		"P1平均压太高"   									//高	//P1平均压超过报警高限
#define		G_WARN_P_TXT_IBP7NMLOW		"P1平均压太低"   									//高	//P1平均压低于报警低限
#define		G_WARN_P_TXT_IBP7NDHIGH		"P1舒张压太高"   									//高	//P1舒张压超过报警高限
#define		G_WARN_P_TXT_IBP7NDLOW		"P1舒张压太低"   									//高	//P1舒张压低于报警低限
#define		G_WARN_P_TXT_IBP8NSHIGH		"P2压太高"     									//高	//P2收缩压超过报警高限
#define		G_WARN_P_TXT_IBP8NSLOW		"P2压太低"     									//高	//P2收缩压低于报警低限
#define		G_WARN_P_TXT_IBP8NMHIGH		"P2平均压太高"   									//高	//P2平均压超过报警高限
#define		G_WARN_P_TXT_IBP8NMLOW		"P2平均压太低"   									//高	//P2平均压低于报警低限
#define		G_WARN_P_TXT_IBP8NDHIGH		"P2舒张压太高"   									//高	//P2舒张压超过报警高限
#define		G_WARN_P_TXT_IBP8NDLOW		"P2舒张压太低"   									//高	//P2舒张压低于报警低限
#define		G_WARN_P_TXT_ETCO2HIGH		"呼末CO₂太高"   									//中	//呼末CO₂超过报警高限
#define		G_WARN_P_TXT_ETCO2LOW		"呼末CO₂太低"   									//中	//呼末CO₂低于报警低限
#define		G_WARN_P_TXT_FICO2HIGH		"吸末CO₂太高"   									//中	//吸末CO₂超过报警高限
#define		G_WARN_P_TXT_FICO2LOW		"吸末CO₂太低"   									//中	//吸末CO₂低于报警低限
#define		G_WARN_P_TXT_SPHIGH		"气道呼吸率太高"   									//中	//气道呼吸率超过报警高限
#define		G_WARN_P_TXT_SPLOW		"气道呼吸率太低"   									//中	//气道呼吸率低于报警低限

//	报警信息	触发条件		报警优先级
#define		G_WARN_T_TXT_ECGLEADOFF		"心电导联脱落"    			//低	//RL或2个以上的心电导联脱落
#define		G_WARN_T_TXT_RALEADOFF		"心电导联RA脱落"  			//低	//RA导联脱落
#define		G_WARN_T_TXT_LALEADOFF		"心电导联LA脱落"  			//低	//LA导联脱落
#define		G_WARN_T_TXT_LLLEADOFF		"心电导联LL脱落"  			//低	//LL导联脱落
#define		G_WARN_T_TXT_VLEADOFF		"心电导联V脱落"   			//低	//V导联脱落
#define		G_WARN_T_TXT_MODUINITERR	"模块初始化错"    			//低	//模块自检错误
#define		G_WARN_T_TXT_COMMSTOP		"模块通讯停止"   			//低	//模块和主机通讯出现问题
#define		G_WARN_T_TXT_COMMERR		"模块通讯错"     			//低	//模块和主机通讯出现问题
#define		G_WARN_T_TXT_WARNLIMITERR		"参数报警限错"    			//低	//参数的报警限被意外改动
#define		G_WARN_T_TXT_PARALIMITERR		"测量范围超界"    			//低	//参数的测量值超出了系统所能进行的测量范围
#define		G_WARN_T_TXT_SPO2SENSER		"血氧探头脱落"    			//低	//血氧探头未接好
#define		G_WARN_T_TXT_SPO2FINGER		"血氧探头手指脱落"  			//低	//手指从血氧探头中脱落
#define		G_WARN_T_TXT_SEARCHPULSE	"搜索脉搏... "  			//低	//血氧探头没有连接好或病人运动手臂
#define		G_WARN_T_TXT_TEMP1SENSOR		"体温通道1探头脱落" 			//低	//体温通道1探头未接好
#define		G_WARN_T_TXT_TEMP2SENSOR		"体温通道2探头脱落" 			//低	//体温通道2探头未接好
#define		G_WARN_T_TXT_WATCHDOGERR	"看门狗错误"     			//低	//主机看门狗自检失败
#define		G_WARN_T_TXT_SYSTIMEERR	"系统时间丢失"    			//低	//系统时钟未设置
#define		G_WARN_T_TXT_12VHIGH	"12V电压太高"  			//低	//12V电压检测超出正常电压范围
#define		G_WARN_T_TXT_12VLOW	"12V电压太低"  			//低	//12V电压检测低于正常电压范围
#define		G_WARN_T_TXT_3_3VHIGH	"3.3V电压太高"  			//低	//3.3V电压检测超出正常电压范围
#define		G_WARN_T_TXT_3_3VLOW	"3.3V电压太低"  			//低	//3.3V电压检测低于正常电压范围
#define		G_WARN_T_TXT_BATHIGH	"电池电压太高"    			//低	//电池电压检测超出正常电压范围
#define		G_WARN_T_TXT_BATLOW		"电池不足，请立即充电"			//低	//电池电量不足
#define		G_WARN_T_TXT_TIELOOSE	"无创血压袖带松"    			//低	//袖带未连接好
#define		G_WARN_T_TXT_NBPLEAK		"无创血压漏气"     			//低	//袖带未连接好或气路漏气
#define		G_WARN_T_TXT_NBPAIRERR		"无创血压放气错误"   			//低	//血压测量时放气出现问题
#define		G_WARN_T_TXT_NBPWEAK		"无创血压信号太弱"   			//低	//血压测量时脉搏信号太弱，无法计算出血压
#define		G_WARN_T_TXT_NBPEXD		"无创血压测量超界"   			//低	//血压测量时血压或脉搏信号超出正常范围，无法进行测量
#define		G_WARN_T_TXT_NBPMOVE		"无创血压手臂运动"   			//低	//病人手臂运动
#define		G_WARN_T_TXT_NBPOVERPRESSURE		"无创血压过压"    			//低	//压力值超过测量范围
#define		G_WARN_T_TXT_NBPSAT		"无创血压信号饱和"   			//低	//血压测量时脉搏信号超出正常范围，无法进行测量
#define		G_WARN_T_TXT_NBPLEAKCKFAIL	"无创血压漏气检测失败" 			//低	//袖带未连接好或气路漏气
#define		G_WARN_T_TXT_NBPFAIL		"无创血压系统错误"  			//低	//血压系统自检失败，一般是压力传感器实效导致自检失败
#define		G_WARN_T_TXT_NBPTIMEOUT		"无创血压测量超时"  			//低	//血压测量超时
#define		G_WARN_T_TXT_NBPTIEERR	"无创血压袖带类型错" 			//低	//病人类型为成人时使用了新生儿袖带
#define		G_WARN_T_TXT_NBPMESSUREFAIL 	"无创血压测量失败"  			//低	//本次血压测量未能计算出血压
#define		G_WARN_T_TXT_NBPRESETERR	"无创血压非法复位"  			//低	//血压测量时异常复位
#define		G_WARN_T_TXT_CO2STANDBY	"CO₂待命"     			//低	//CO₂处于待命状态
#define		G_WARN_T_TXT_CO2STOP		"CO₂通讯停止"  			//低	//CO₂模块和主机通讯出现问题
#define       G_WARN_T_TXT_HEARTV             " "  //心跳

//声音文件
#define  G_WARN_FILE_PATH   "/home/data/wav/"
#define     G_WARN_NO_WARNING                       "heart.wav"        //无报警
#define		G_WARN_P_FILE_ASYSTOLE				"asystole_cn.wav" 			// * * *心脏停搏	超过4秒钟无心跳信号	高
#define		G_WARN_P_FILE_APNEA						"apnea_cn.wav" 			// * * *呼吸窒息	超过设定的呼吸窒息时间无呼吸信号	高
#define		G_WARN_P_FILE_NOPULSE				"nopulse_cn.wav" 			// * * *无脉搏	超过15秒无脉搏信号	高
#define		G_WARN_P_FILE_HRHIGH					"heart.wav" 			// * * 心率太高	心率超过报警高限	高
#define		G_WARN_P_FILE_HRHLOW					"heart.wav" 			// * * 心率太低	心率低于报警低限	高
#define		G_WARN_P_FILE_ST1HIGH					"heart.wav" 			// * * ST-I太高	I导联ST值超过报警高限	高
#define		G_WARN_P_FILE_ST1LOW					"heart.wav" 			// * * ST-I太低	I导联ST值低于报警低限	高
#define		G_WARN_P_FILE_ST2HIGH					"heart.wav" 			// * * ST-II太高	II导联ST值超过报警高限	高
#define		G_WARN_P_FILE_ST2LOW					"heart.wav" 			// * * ST-II太低	II导联ST值低于报警低限	高
#define		G_WARN_P_FILE_ST3HIGH					"heart.wav" 			// * * ST-III太高	III导联ST值超过报警高限	高
#define		G_WARN_P_FILE_ST3LOW					"heart.wav" 			// * * ST-III太低	III导联ST值低于报警低限	高
#define		G_WARN_P_FILE_STAVRHIGH	  		"heart.wav" 			// * * ST-AVR太高	AVR导联ST值超过报警高限	高
#define		G_WARN_P_FILE_STAVRLOW	  		"heart.wav" 			// * * ST-AVR太低	AVR导联ST值低于报警低限	高
#define		G_WARN_P_FILE_STAVLHIGH	  		"heart.wav" 			// * * ST-AVL太高	AVL导联ST值超过报警高限	高
#define		G_WARN_P_FILE_STAVLLOW	  		"heart.wav" 			// * * ST-AVL太低	AVL导联ST值低于报警低限	高
#define		G_WARN_P_FILE_STAVFHIGH				"heart.wav"			// * * ST-AVF太高	AVF导联ST值超过报警高限	高
#define		G_WARN_P_FILE_STAVFLOW	  		"heart.wav"			// * * ST-AVF太低	AVF导联ST值低于报警低限	高
#define		G_WARN_P_FILE_STVHIGH	    		"heart.wav"			// * * ST-V太高	V导联ST值超过报警高限	高
#define		G_WARN_P_FILE_STVLOW		  		"heart.wav"			// * * ST-V太低	V导联ST值低于报警低限	高
#define		G_WARN_P_FILE_PVCHIGH	    		"heart.wav"			// * * PVCs太高	PVCs值超过报警高限	高
#define		G_WARN_P_FILE_SPO2HIGH	  		"heart.wav"			// * * 氧饱和度太高	氧饱和度超过报警高限	中
#define		G_WARN_P_FILE_SPO2LOW		  		"heart.wav"			// * * 氧饱和度太低	氧饱和度低于报警低限	中
#define		G_WARN_P_FILE_PRHIGH		  		"heart.wav"			// * * 脉率太高	脉率超过报警高限	中
#define		G_WARN_P_FILE_PRLOW			  		"heart.wav"			// * * 脉率太低	脉率低于报警低限	中
#define		G_WARN_P_FILE_NSHIGH					"heart.wav"			// * * 收缩压太高	收缩压超过报警高限	中
#define		G_WARN_P_FILE_NSLOW						"heart.wav"			// * * 收缩压太低	收缩压低于报警低限	中
#define		G_WARN_P_FILE_NMHIGH					"heart.wav"			// * * 平均压太高	平均压超过报警高限	中
#define		G_WARN_P_FILE_NMLOW						"heart.wav"			// * * 平均压太低	平均压低于报警低限	中
#define		G_WARN_P_FILE_NDHIGH					"heart.wav"			// * * 舒张压太高	舒张压超过报警高限	中
#define		G_WARN_P_FILE_NDLOW						"heart.wav"			// * * 舒张压太低	舒张压低于报警低限	中
#define		G_WARN_P_FILE_RRHIGH					"heart.wav"			// * * 呼吸率太高	呼吸率超过报警高限	中
#define		G_WARN_P_FILE_RRLOW						"heart.wav"			// * * 呼吸率太低	呼吸率低于报警低限	中
#define		G_WARN_P_FILE_TEMP1HIGH	  		"heart.wav"			// * * 体温通道1太高	体温通道1超过报警高限	中
#define		G_WARN_P_FILE_TEMP1LOW	  		"heart.wav"			// * * 体温通道1太低	体温通道1低于报警低限	中
#define		G_WARN_P_FILE_TEMP2HIGH	  		"heart.wav"			// * * 体温通道2太高	体温通道2超过报警高限	中
#define		G_WARN_P_FILE_TEMP2LOW	  		"heart.wav"			// * * 体温通道2太低	体温通道2低于报警低限	中
#define		G_WARN_P_FILE_IBP1NSHIGH	        		"heart.wav"			// * * 主动脉压收缩压太高	主动脉收缩压超过报警高限	中
#define		G_WARN_P_FILE_IBP1NSLOW	        		"heart.wav"			// * * 主动脉压收缩压太低	主动脉收缩压低于报警低限	中
#define		G_WARN_P_FILE_IBP1NMHIGH	        		"heart.wav"			// * * 主动脉压平均压太高	主动脉平均压超过报警高限	中
#define		G_WARN_P_FILE_IBP1NMLOW		        		"heart.wav"			// * * 主动脉压平均压太低	主动脉平均压低于报警低限	中
#define		G_WARN_P_FILE_IBP1NDHIGH	        		"heart.wav"			// * * 主动脉压舒张压太高	主动脉舒张压超过报警高限	中
#define		G_WARN_P_FILE_IBP1NDLOW	        		"heart.wav"			// * * 肺动脉压舒张压太低	肺动脉舒张压低于报警低限	中
#define		G_WARN_P_FILE_IBP2NSHIGH	        		"heart.wav"			// * * 肺动脉压收缩压太高	肺动脉收缩压超过报警高限	中
#define		G_WARN_P_FILE_IBP2NSLOW		        		"heart.wav"			// * * 肺动脉压收缩压太低	肺动脉收缩压低于报警低限	中
#define		G_WARN_P_FILE_IBP2NMHIGH	        		"heart.wav"			// * * 肺动脉压平均压太高	肺动脉平均压超过报警高限	中
#define		G_WARN_P_FILE_IBP2NMLOW	        		"heart.wav"			// * * 肺动脉压平均压太低	肺动脉平均压低于报警低限	中
#define		G_WARN_P_FILE_IBP2NDHIGH	        		"heart.wav"			// * * 肺动脉压舒张压太高	肺动脉舒张压超过报警高限	中
#define		G_WARN_P_FILE_IBP2NDLOW	        		"heart.wav"			// * * 肺动脉压舒张压太低	肺动脉舒张压低于报警低限	中
#define		G_WARN_P_FILE_IBP3NSHIGH	        		"heart.wav"			// * * 中心静脉压收缩压太高	中心静脉收缩压超过报警高限	中
#define		G_WARN_P_FILE_IBP3NSLOW	        		"heart.wav"			// * * 中心静脉压收缩压太低	中心静脉收缩压低于报警低限	中
#define		G_WARN_P_FILE_IBP3NMHIGH	        		"heart.wav"			// * * 中心静脉压平均压太高	中心静脉平均压超过报警高限	中
#define		G_WARN_P_FILE_IBP3NMLOW	        		"heart.wav"			// * * 中心静脉压平均压太低	中心静脉平均压低于报警低限	中
#define		G_WARN_P_FILE_IBP3NDHIGH	        		"heart.wav"			// * * 中心静脉压舒张压太高	中心静脉舒张压超过报警高限	中
#define		G_WARN_P_FILE_IBP3NDLOW	        		"heart.wav"			// * * 中心静脉压舒张压太低	中心静脉舒张压低于报警低限	中
#define		G_WARN_P_FILE_IBP4NSHIGH		        		"heart.wav"			// * * 左房压收缩压太高	左房收缩压超过报警高限	中
#define		G_WARN_P_FILE_IBP4NSLOW	        		"heart.wav"			// * * 左房压收缩压太低	左房收缩压低于报警低限	中
#define		G_WARN_P_FILE_IBP4NMHIGH		        		"heart.wav"			// * * 左房压平均压太高	左房平均压超过报警高限	中
#define		G_WARN_P_FILE_IBP4NMLOW			        		"heart.wav"			// * * 左房压平均压太低	左房平均压低于报警低限	中
#define		G_WARN_P_FILE_IBP4NDHIGH		        		"heart.wav"			// * * 左房压舒张压太高	左房舒张压超过报警高限	中
#define		G_WARN_P_FILE_IBP4NDLOW			        		"heart.wav"			// * * 左房压舒张压太低	左房舒张压低于报警低限	中
#define		G_WARN_P_FILE_IBP5NSHIGH		        		"heart.wav"			// * * 右房压收缩压太高	右房收缩压超过报警高限	中
#define		G_WARN_P_FILE_IBP5NSLOW			        		"heart.wav"			// * * 右房压收缩压太低	右房收缩压低于报警低限	中
#define		G_WARN_P_FILE_IBP5NMHIGH		        		"heart.wav"			// * * 右房压平均压太高	右房平均压超过报警高限	中
#define		G_WARN_P_FILE_IBP5NMLOW			        		"heart.wav"			// * * 右房压平均压太低	右房平均压低于报警低限	中
#define		G_WARN_P_FILE_IBP5NDHIGH		        		"heart.wav"			// * * 右房压舒张压太高	右房舒张压超过报警高限	中
#define		G_WARN_P_FILE_IBP5NDLOW			        		"heart.wav"			// * * 右房压舒张压太低	右房舒张压低于报警低限	中
#define		G_WARN_P_FILE_IBP6NSHIGH		        		"heart.wav"			// * * 颅内压收缩压太高	颅内收缩压超过报警高限	中
#define		G_WARN_P_FILE_IBP6NSLOW			        		"heart.wav"			// * * 颅内压收缩压太低	颅内收缩压低于报警低限	中
#define		G_WARN_P_FILE_IBP6NMHIGH		        		"heart.wav"			// * * 颅内压平均压太高	颅内平均压超过报警高限	中
#define		G_WARN_P_FILE_IBP6NMLOW			        		"heart.wav"			// * * 颅内压平均压太低	颅内平均压低于报警低限	高
#define		G_WARN_P_FILE_IBP6NDHIGH		        		"heart.wav"			// * * 颅内压舒张压太高	颅内舒张压超过报警高限	高
#define		G_WARN_P_FILE_IBP6NDLOW			        		"heart.wav"			// * * 颅内压舒张压太低	颅内舒张压低于报警低限	高
#define		G_WARN_P_FILE_IBP7NSHIGH		        		"heart.wav"			// * * P1压太高	P1收缩压超过报警高限	高
#define		G_WARN_P_FILE_IBP7NSLOW			        		"heart.wav"			// * * P1压太低	P1收缩压低于报警低限	高
#define		G_WARN_P_FILE_IBP7NMHIGH		        		"heart.wav"			// * * P1平均压太高	P1平均压超过报警高限	高
#define		G_WARN_P_FILE_IBP7NMLOW			        		"heart.wav"			// * * P1平均压太低	P1平均压低于报警低限	高
#define		G_WARN_P_FILE_IBP7NDHIGH		        		"heart.wav"			// * * P1舒张压太高	P1舒张压超过报警高限	高
#define		G_WARN_P_FILE_IBP7NDLOW			        		"heart.wav"			// * * P1舒张压太低	P1舒张压低于报警低限	高
#define		G_WARN_P_FILE_IBP8NSHIGH		        		"heart.wav"			// * * P2压太高	P2收缩压超过报警高限	高
#define		G_WARN_P_FILE_IBP8NSLOW			        		"heart.wav"			// * * P2压太低	P2收缩压低于报警低限	高
#define		G_WARN_P_FILE_IBP8NMHIGH		        		"heart.wav"			// * * P2平均压太高	P2平均压超过报警高限	高
#define		G_WARN_P_FILE_IBP8NMLOW			        		"heart.wav"			// * * P2平均压太低	P2平均压低于报警低限	高
#define		G_WARN_P_FILE_IBP8NDHIGH		        		"heart.wav"			// * * P2舒张压太高	P2舒张压超过报警高限	高
#define		G_WARN_P_FILE_IBP8NDLOW			        		"heart.wav"			// * * P2舒张压太低	P2舒张压低于报警低限	高
#define		G_WARN_P_FILE_ETCO2HIGH         "heart.wav"			// * * 呼末CO₂太高	呼末CO₂超过报警高限	中
#define		G_WARN_P_FILE_ETCO2LOW          "heart.wav"			// * * 呼末CO₂太低	呼末CO₂低于报警低限	中
#define		G_WARN_P_FILE_FICO2HIGH		        		"heart.wav"			// * * 吸末CO₂太高	吸末CO₂超过报警高限	中
#define		G_WARN_P_FILE_FICO2LOW	        		"heart.wav"			// * * 吸末CO₂太低	吸末CO₂低于报警低限	中
#define		G_WARN_P_FILE_SPHIGH	        		"heart.wav"			// * * 气道呼吸率太高	气道呼吸率超过报警高限	中
#define		G_WARN_P_FILE_SPLOW	        		"heart.wav"  		// * * 气道呼吸率太低	气道呼吸率低于报警低限	中


//		报警信息	触发条件		报警优先级
#define		G_WARN_T_FILE_ECGLEADOFF     "heart.wav"			// * * 心电导联脱落	RL或2个以上的心电导联脱落		低
#define		G_WARN_T_FILE_RALEADOFF         "heart.wav"			// * * 心电导联RA脱落	RA导联脱落		低
#define		G_WARN_T_FILE_LALEADOFF         "heart.wav"			// * * 心电导联LA脱落	LA导联脱落		低
#define		G_WARN_T_FILE_LLLEADOFF         "heart.wav"			// * * 心电导联LL脱落	LL导联脱落		低
#define		G_WARN_T_FILE_VLEADOFF           "heart.wav"			// * * 心电导联V脱落	V导联脱落		低
#define		G_WARN_T_FILE_MODUINITERR    "heart.wav"			// * * 模块初始化错	模块自检错误		低
#define		G_WARN_T_FILE_COMMSTOP				  		"heart.wav"			// * * *模块通讯停止	模块和主机通讯出现问题		低
#define		G_WARN_T_FILE_COMMERR							"heart.wav"			// * * 模块通讯错	模块和主机通讯出现问题		低
#define		G_WARN_T_FILE_WARNLIMITERR								  		"heart.wav"			// * * 参数报警限错	参数的报警限被意外改动		低
#define		G_WARN_T_FILE_PARALIMITERR								  		"heart.wav"			// * * 测量范围超界	参数的测量值超出了系统所能进行的测量范围		低
#define		G_WARN_T_FILE_SPO2SENSER			  		"heart.wav"			// * * 血氧探头脱落	血氧探头未接好		低
#define		G_WARN_T_FILE_SPO2FINGER			  		"heart.wav"			// * * 血氧探头手指脱落	手指从血氧探头中脱落		低
#define		G_WARN_T_FILE_SEARCHPULSE							  		"heart.wav"			// * * 搜索脉搏...	血氧探头没有连接好或病人运动手臂		低
#define		G_WARN_T_FILE_TEMP1SENSOR					"heart.wav"			// * * 体温通道1探头脱落	体温通道1探头未接好		低
#define		G_WARN_T_FILE_TEMP2SENSOR					"heart.wav"			// * * 体温通道2探头脱落	体温通道2探头未接好		低
#define		G_WARN_T_FILE_WATCHDOGERR							  		"heart.wav"			// * * 看门狗错误	主机看门狗自检失败		低
#define		G_WARN_T_FILE_SYSTIMEERR								  		"heart.wav"			// * * 系统时间丢失	系统时钟未设置		低
#define		G_WARN_T_FILE_12VHIGH							  		"heart.wav"			// * * 12V电压太高	12V电压检测超出正常电压范围		低
#define		G_WARN_T_FILE_12VLOW							  		"heart.wav"			// * * 12V电压太低	12V电压检测低于正常电压范围		低
#define		G_WARN_T_FILE_3_3VHIGH							  		"heart.wav"			// * * 3.3V电压太高	3.3V电压检测超出正常电压范围		低
#define		G_WARN_T_FILE_3_3VLOW							  		"heart.wav"			// * * 3.3V电压太低	3.3V电压检测低于正常电压范围		低
#define		G_WARN_T_FILE_BATHIGH							  		"heart.wav"			// * * 电池电压太高	电池电压检测超出正常电压范围		低
#define		G_WARN_T_FILE_BATLOW							  		"batlow_cn.wav"			// * * 电池不足，请立即充电	电池电量不足		低
#define		G_WARN_T_FILE_TIELOOSE							  		"heart.wav"			// * 无创血压袖带松	袖带未连接好		低
#define		G_WARN_T_FILE_NBPLEAK							"heart.wav"			// * 无创血压漏气	袖带未连接好或气路漏气		低
#define		G_WARN_T_FILE_NBPAIRERR						"heart.wav"			// * 无创血压放气错误	血压测量时放气出现问题		低
#define		G_WARN_T_FILE_NBPWEAK							"heart.wav"			// * 无创血压信号太弱	血压测量时脉搏信号太弱，无法计算出血压		低
#define		G_WARN_T_FILE_NBPEXD					  		"heart.wav"			// * 无创血压测量超界	血压测量时血压或脉搏信号超出正常范围，无法进行测量		低
#define		G_WARN_T_FILE_NBPMOVE							"heart.wav"			// * 无创血压手臂运动	病人手臂运动		低
#define		G_WARN_T_FILE_NBPOVERPRESSURE			"heart.wav"			// * * 无创血压过压	压力值超过测量范围		低
#define		G_WARN_T_FILE_NBPSAT					  		"heart.wav"			// * 无创血压信号饱和	血压测量时脉搏信号超出正常范围，无法进行测量		低
#define		G_WARN_T_FILE_NBPLEAKCKFAIL							  		"heart.wav"			// * 无创血压漏气检测失败	袖带未连接好或气路漏气		低
#define		G_WARN_T_FILE_NBPFAIL							"heart.wav"			// * * 无创血压系统错误	血压系统自检失败，一般是压力传感器实效导致自检失败		低
#define		G_WARN_T_FILE_NBPTIMEOUT			  		"heart.wav"			// * * 无创血压测量超时	血压测量超时		低
#define		G_WARN_T_FILE_NBPTIEERR							  		"heart.wav"			// * * 无创血压袖带类型错	病人类型为成人时使用了新生儿袖带		低
#define		G_WARN_T_FILE_NBPMESSUREFAIL		  		"heart.wav"			// * * 无创血压测量失败	本次血压测量未能计算出血压		低
#define		G_WARN_T_FILE_NBPRESETERR							  		"heart.wav"			// * * 无创血压非法复位	血压测量时异常复位		低
#define		G_WARN_T_FILE_CO2STANDBY								  		"heart.wav"			// * * CO₂待命	CO₂处于待命状态		低
#define		G_WARN_T_FILE_CO2STOP							  		"heart.wav"			// * * *CO₂通讯停止	CO₂模块和主机通讯出现问题		低
#define      G_WARN_T_FILE_HEARTV   "heart.wav"



//优先级代码
#define G_WARN_PRIORITY_HIGH 0
#define G_WARN_PRIORITY_MID 1
#define G_WARN_PRIORITY_LOW 2
//报警暂停
#define G_WARN_PAUSE_ON  0 //报警不暂停
#define G_WARN_PAUSE_OFF 1 //报警暂停
//报警暂停时间
#define G_WARN_PAUSE_TIME_1 0 //暂停1分钟
#define G_WARN_PAUSE_TIME_2 1 //暂停2分钟
//参数报警栓锁
#define G_WARN_PARA_LOCK_OFF 0 //参数报警非栓锁
#define G_WARN_PARA_LOCK_ON 1 //参数报警栓锁
//报警记录开关
#define G_WARN_RECORD_ON 0 //参数报警记录开
#define G_WARN_RECORD_OFF 1 //参数报警记录关
//语音报警开关
#define G_WARN_VOICE_ON 0  //语音报警开
#define G_WARN_VOICE_OFF 1 //语音报警关
//报警音量
#define G_WARN_VOICE_VOL_0 0
#define G_WARN_VOICE_VOL_1 1
#define G_WARN_VOICE_VOL_2 2
#define G_WARN_VOICE_VOL_3 3
//参数报警解除方式
#define G_WARN_PARA_DEL_KEY 0    //按键解除参数报警
#define G_WARN_PARA_DEL_AUTO 1 //自动解除参数报警
//shanshuo kai guan
#define G_WARN_CORUSECATE_ON 0
#define G_WARN_CORUSECATE_OFF 1
//报警配置文档
#define G_WARN_CFG_DOC "/home/data/config/warning.dat"
//报警配置结构体
typedef struct stWarnCfg_
{
    int m_warn_corusecate;  //闪烁
    int m_warn_pause_time ;//报警暂停时间G_WARN_PAUSE_TIME_1，1分钟；G_WARN_PAUSE_TIME_2，2分钟。
    int m_warn_para_lock; //参数报警是否栓锁
    int m_warn_record_flg; //报警记录开关标志G_WARN_RECORD_ON，记录；G_WARN_RECORD_OFF，不记录。
    int m_warn_voice_flg;
    int m_warn_voice_volume;

    int m_warn_pause_flg;    //报警暂停标志,G_WARN_PAUSE_OFF不暂停，G_WARN_PAUSE_ON暂停
}stWarnCfg;

class CGlbWarn
{
public:
    CGlbWarn();
    ~CGlbWarn();
public:

    QList<int> m_warn_code_high;
    QList<int> m_warn_code_mid;
    QList<int> m_warn_code_low;
    QList<QString> m_warn_txt_high;
    QList<QString> m_warn_txt_mid;
    QList<QString> m_warn_txt_low;

private:
    stWarnCfg m_stWarnCfg;

public:
    void f_addWarn(int iWarnCode,QString strWarnTxt,int iWarnPriority);
    void f_readWarn(int *iWarnCode, QString *strWarnTxt, int *iWarnPri);
    void f_setConfig(stWarnCfg);
    void f_getConfig(stWarnCfg *);
    void f_delWarn(int iMethod,int iWarnCode);
    void f_setDefaultCfg();
private:

};
extern CGlbWarn * g_WarningCfg;
extern QString g_WarningName[];
extern QString g_WarningFile[];
//extern int g_WarningCode[G_WARN_MAX_COUNT];
extern int g_WarningPri[G_WARN_MAX_COUNT];
#endif // GLB_WARNING_H
