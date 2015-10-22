#include "glb_warning.h"
#include <QFile>
 #include <QDataStream>

CGlbWarn * g_WarningCfg;
/*
int g_WarningCode[] = {

            G_WARN_P_CODE_ASYSTOLE				 			//  * * *心脏停搏	超过4秒钟无心跳信号	高
    ,		G_WARN_P_CODE_APNEA									//  * * *呼吸窒息	超过设定的呼吸窒息时间无呼吸信号	高
    ,		G_WARN_P_CODE_NOPULSE				 			//  * * *无脉搏	超过15秒无脉搏信号	高
    ,		G_WARN_P_CODE_HRHIGH								//  * * 心率太高	心率超过报警高限	高
    ,		G_WARN_P_CODE_HRLOW					 			//  * * 心率太低	心率低于报警低限	高
    ,		G_WARN_P_CODE_ST1HIGH					 			//  * * ST-I太高	I导联ST值超过报警高限	高
    ,		G_WARN_P_CODE_ST1LOW					 			//  * * ST-I太低	I导联ST值低于报警低限	高
    ,		G_WARN_P_CODE_ST2HIGH					 			//  * * ST-II太高	II导联ST值超过报警高限	高
    ,		G_WARN_P_CODE_ST2LOW					 			//  * * ST-II太低	II导联ST值低于报警低限	高
    ,		G_WARN_P_CODE_ST3HIGH					 			//  * * ST-III太高	III导联ST值超过报警高限	高
    ,		G_WARN_P_CODE_ST3LOW					 			//  * * ST-III太低	III导联ST值低于报警低限	高
    ,		G_WARN_P_CODE_STAVRHIGH	  		 			//  * * ST-AVR太高	AVR导联ST值超过报警高限	高
    ,		G_WARN_P_CODE_STAVRLOW	  		 			//  * * ST-AVR太低	AVR导联ST值低于报警低限	高
    ,		G_WARN_P_CODE_STAVLHIGH	  		 			//  * * ST-AVL太高	AVL导联ST值超过报警高限	高
    ,		G_WARN_P_CODE_STAVLLOW	  		 			//  * * ST-AVL太低	AVL导联ST值低于报警低限	高
    ,		G_WARN_P_CODE_STAVFHIGH						//  * * ST-AVF太高	AVF导联ST值超过报警高限	高
    ,		G_WARN_P_CODE_STAVFLOW	  					//  * * ST-AVF太低	AVF导联ST值低于报警低限	高
    ,		G_WARN_P_CODE_STVHIGH	    					//  * * ST-V太高	V导联ST值超过报警高限	高
    ,		G_WARN_P_CODE_STVLOW		  					//  * * ST-V太低	V导联ST值低于报警低限	高
    ,		G_WARN_P_CODE_PVCHIGH	    					//  * * PVCs太高	PVCs值超过报警高限	高
    ,		G_WARN_P_CODE_SPO2HIGH	  					//  * * 氧饱和度太高	氧饱和度超过报警高限	中
    ,		G_WARN_P_CODE_SPO2LOW		  					//  * * 氧饱和度太低	氧饱和度低于报警低限	中
    ,		G_WARN_P_CODE_PRHIGH		  					//  * * 脉率太高	脉率超过报警高限	中
    ,		G_WARN_P_CODE_PRLOW			  					//  * * 脉率太低	脉率低于报警低限	中
    ,		G_WARN_P_CODE_NSHIGH								//  * * 收缩压太高	收缩压超过报警高限	中
    ,		G_WARN_P_CODE_NSLOW									//  * * 收缩压太低	收缩压低于报警低限	中
    ,		G_WARN_P_CODE_NMHIGH								//  * * 平均压太高	平均压超过报警高限	中
    ,		G_WARN_P_CODE_NMLOW									//  * * 平均压太低	平均压低于报警低限	中
    ,		G_WARN_P_CODE_NDHIGH								//  * * 舒张压太高	舒张压超过报警高限	中
    ,		G_WARN_P_CODE_NDLOW									//  * * 舒张压太低	舒张压低于报警低限	中
    ,		G_WARN_P_CODE_RRHIGH								//  * * 呼吸率太高	呼吸率超过报警高限	中
    ,		G_WARN_P_CODE_RRLOW									//  * * 呼吸率太低	呼吸率低于报警低限	中
    ,		G_WARN_P_CODE_TEMP1HIGH	  					//  * * 体温通道1太高	体温通道1超过报警高限	中
    ,		G_WARN_P_CODE_TEMP1LOW	  					//  * * 体温通道1太低	体温通道1低于报警低限	中
    ,		G_WARN_P_CODE_TEMP2HIGH	  					//  * * 体温通道2太高	体温通道2超过报警高限	中
    ,		G_WARN_P_CODE_TEMP2LOW	  					//  * * 体温通道2太低	体温通道2低于报警低限	中
    ,		G_WARN_P_CODE_IBP1NSHIGH	        					//  * * 主动脉压收缩压太高	主动脉收缩压超过报警高限	中
    ,		G_WARN_P_CODE_IBP1NSLOW	        					//  * * 主动脉压收缩压太低	主动脉收缩压低于报警低限	中
    ,		G_WARN_P_CODE_IBP1NMHIGH	        					//  * * 主动脉压平均压太高	主动脉平均压超过报警高限	中
    ,		G_WARN_P_CODE_IBP1NMLOW		        				//  * * 主动脉压平均压太低	主动脉平均压低于报警低限	中
    ,		G_WARN_P_CODE_IBP1NDHIGH	        					//  * * 主动脉压舒张压太高	主动脉舒张压超过报警高限	中
    ,		G_WARN_P_CODE_IBP1NDLOW	        					//  * * 肺动脉压舒张压太低	肺动脉舒张压低于报警低限	中
    ,		G_WARN_P_CODE_IBP2NSHIGH	        					//  * * 肺动脉压收缩压太高	肺动脉收缩压超过报警高限	中
    ,		G_WARN_P_CODE_IBP2NSLOW		        				//  * * 肺动脉压收缩压太低	肺动脉收缩压低于报警低限	中
    ,		G_WARN_P_CODE_IBP2NMHIGH	        					//  * * 肺动脉压平均压太高	肺动脉平均压超过报警高限	中
    ,		G_WARN_P_CODE_IBP2NMLOW	        					//  * * 肺动脉压平均压太低	肺动脉平均压低于报警低限	中
    ,		G_WARN_P_CODE_IBP2NDHIGH	        					//  * * 肺动脉压舒张压太高	肺动脉舒张压超过报警高限	中
    ,		G_WARN_P_CODE_IBP2NDLOW	        					//  * * 肺动脉压舒张压太低	肺动脉舒张压低于报警低限	中
    ,		G_WARN_P_CODE_IBP3NSHIGH	        					//  * * 中心静脉压收缩压太高	中心静脉收缩压超过报警高限	中
    ,		G_WARN_P_CODE_IBP3NSLOW	        					//  * * 中心静脉压收缩压太低	中心静脉收缩压低于报警低限	中
    ,		G_WARN_P_CODE_IBP3NMHIGH	        					//  * * 中心静脉压平均压太高	中心静脉平均压超过报警高限	中
    ,		G_WARN_P_CODE_IBP3NMLOW	        					//  * * 中心静脉压平均压太低	中心静脉平均压低于报警低限	中
    ,		G_WARN_P_CODE_IBP3NDHIGH	        					//  * * 中心静脉压舒张压太高	中心静脉舒张压超过报警高限	中
    ,		G_WARN_P_CODE_IBP3NDLOW	        					//  * * 中心静脉压舒张压太低	中心静脉舒张压低于报警低限	中
    //,		G_WARN_P_CODE_IBP4NS		        					//  * * 左房压收缩压太高	左房收缩压超过报警高限	中
    //,		G_WARN_P_CODE_IBP4NS		        					//  * * 左房压收缩压太低	左房收缩压低于报警低限	中
    //,		G_WARN_P_CODE_IBP4NM		        					//  * * 左房压平均压太高	左房平均压超过报警高限	中
    //,		G_WARN_P_CODE_IBP4NM		        					//  * * 左房压平均压太低	左房平均压低于报警低限	中
    //,		G_WARN_P_CODE_IBP4ND		        					//  * * 左房压舒张压太高	左房舒张压超过报警高限	中
    //,		G_WARN_P_CODE_IBP4ND		        					//  * * 左房压舒张压太低	左房舒张压低于报警低限	中
    //,		G_WARN_P_CODE_IBP5NS		        					//  * * 右房压收缩压太高	右房收缩压超过报警高限	中
    //,		G_WARN_P_CODE_IBP5NS		        					//  * * 右房压收缩压太低	右房收缩压低于报警低限	中
    //,		G_WARN_P_CODE_IBP5NM		        					//  * * 右房压平均压太高	右房平均压超过报警高限	中
    //,		G_WARN_P_CODE_IBP5NM		        					//  * * 右房压平均压太低	右房平均压低于报警低限	中
    //,		G_WARN_P_CODE_IBP5ND		        					//  * * 右房压舒张压太高	右房舒张压超过报警高限	中
    //,		G_WARN_P_CODE_IBP5ND		        					//  * * 右房压舒张压太低	右房舒张压低于报警低限	中
    //,		G_WARN_P_CODE_IBP6NS		        					//  * * 颅内压收缩压太高	颅内收缩压超过报警高限	中
    //,		G_WARN_P_CODE_IBP6NS		        					//  * * 颅内压收缩压太低	颅内收缩压低于报警低限	中
    //,		G_WARN_P_CODE_IBP6NM		        					//  * * 颅内压平均压太高	颅内平均压超过报警高限	中
    //,		G_WARN_P_CODE_IBP6NM		        					//  * * 颅内压平均压太低	颅内平均压低于报警低限	高
    //,		G_WARN_P_CODE_IBP6ND		        					//  * * 颅内压舒张压太高	颅内舒张压超过报警高限	高
    //,		G_WARN_P_CODE_IBP6ND		        					//  * * 颅内压舒张压太低	颅内舒张压低于报警低限	高
    //,		G_WARN_P_CODE_IBP7NS		        					//  * * P1压太高	P1收缩压超过报警高限	高
    //,		G_WARN_P_CODE_IBP7NS		        					//  * * P1压太低	P1收缩压低于报警低限	高
    //,		G_WARN_P_CODE_IBP7NM		        					//  * * P1平均压太高	P1平均压超过报警高限	高
    //,		G_WARN_P_CODE_IBP7NM		        					//  * * P1平均压太低	P1平均压低于报警低限	高
    //,		G_WARN_P_CODE_IBP7ND		        					//  * * P1舒张压太高	P1舒张压超过报警高限	高
    //,		G_WARN_P_CODE_IBP7ND		        					//  * * P1舒张压太低	P1舒张压低于报警低限	高
    //,		G_WARN_P_CODE_IBP8NS		        					//  * * P2压太高	P2收缩压超过报警高限	高
    //,		G_WARN_P_CODE_IBP8NS		        					//  * * P2压太低	P2收缩压低于报警低限	高
    //,		G_WARN_P_CODE_IBP8NM		        					//  * * P2平均压太高	P2平均压超过报警高限	高
    //,		G_WARN_P_CODE_IBP8NM		        					//  * * P2平均压太低	P2平均压低于报警低限	高
    //,		G_WARN_P_CODE_IBP8ND		        					//  * * P2舒张压太高	P2舒张压超过报警高限	高
    //,		G_WARN_P_CODE_IBP8ND		        					//  * * P2舒张压太低	P2舒张压低于报警低限	高
    ,		G_WARN_P_CODE_CO2HIGH	//  * * 呼末CO₂太高	呼末CO₂超过报警高限	中
    ,		G_WARN_P_CODE_CO2LOW  	//  * * 呼末CO₂太低	呼末CO₂低于报警低限	中
    //,		G_WARN_P_CODE_		        		//  * * 吸末CO₂太高	吸末CO₂超过报警高限	中
    //,		G_WARN_P_CODE_		        		//  * * 吸末CO₂太低	吸末CO₂低于报警低限	中
    ,		G_WARN_P_CODE_SPHIGH	    //  * * 气道呼吸率太高	气道呼吸率超过报警高限	中
    ,		G_WARN_P_CODE_SPLOW	   	//  * * 气道呼吸率太低	气道呼吸率低于报警低限	中
    ,		G_WARN_T_CODE_ECGLEADOFF			  					//  * * 心电导联脱落	RL或2个以上的心电导联脱落		低
    ,		G_WARN_T_CODE_RALEADOFF									//  * * 心电导联RA脱落	RA导联脱落		低
    ,		G_WARN_T_CODE_LALEADOFF									//  * * 心电导联LA脱落	LA导联脱落		低
    ,		G_WARN_T_CODE_LLLEADOFF									//  * * 心电导联LL脱落	LL导联脱落		低
    ,		G_WARN_T_CODE_VLEADOFF				  					//  * * 心电导联V脱落	V导联脱落		低
    ,		G_WARN_T_CODE_MODUINITERR							  					//  * * 模块初始化错	模块自检错误		低
    ,		G_WARN_T_CODE_COMMSTOP				  					//  * * *模块通讯停止	模块和主机通讯出现问题		低
    ,		G_WARN_T_CODE_COMMERR										//  * * 模块通讯错	模块和主机通讯出现问题		低
    //,		G_WARN_T_CODE_								  					//  * * 参数报警限错	参数的报警限被意外改动		低
    //,		G_WARN_T_CODE_								  					//  * * 测量范围超界	参数的测量值超出了系统所能进行的测量范围		低
    ,		G_WARN_T_CODE_SPO2SENSER			  					//  * * 血氧探头脱落	血氧探头未接好		低
    ,		G_WARN_T_CODE_SPO2FINGER			  					//  * * 血氧探头手指脱落	手指从血氧探头中脱落		低
    ,		G_WARN_T_CODE_SEARCHPULSE							  					//  * * 搜索脉搏...	血氧探头没有连接好或病人运动手臂		低
    ,		G_WARN_T_CODE_TEMP1SENSOR								//  * * 体温通道1探头脱落	体温通道1探头未接好		低
    ,		G_WARN_T_CODE_TEMP2SENSOR								//  * * 体温通道2探头脱落	体温通道2探头未接好		低
    ,		G_WARN_T_CODE_WATCHDOGERR							  					//  * * 看门狗错误	主机看门狗自检失败		低
    ,		G_WARN_T_CODE_SYSTIMEERR										//  * * 系统时间丢失	系统时钟未设置		低
    ,		G_WARN_T_CODE_12VHIGH							  					//  * * 12V电压太高	12V电压检测超出正常电压范围		低
    ,		G_WARN_T_CODE_12VLOW							  					//  * * 12V电压太低	12V电压检测低于正常电压范围		低
    ,		G_WARN_T_CODE_3_3VHIGH							  				//  * * 3.3V电压太高	3.3V电压检测超出正常电压范围		低
    ,		G_WARN_T_CODE_3_3VLOW							  					//  * * 3.3V电压太低	3.3V电压检测低于正常电压范围		低
    ,		G_WARN_T_CODE_BATHIGH							  					//  * * 电池电压太高	电池电压检测超出正常电压范围		低
    ,		G_WARN_T_CODE_BATLOW							  					//  * * 电池不足，请立即充电	电池电量不足		低
    ,		G_WARN_T_CODE_TIELOOSE							  					//  *无创血压袖带松	袖带未连接好		低
    ,		G_WARN_T_CODE_NBPLEAK										//  *无创血压漏气	袖带未连接好或气路漏气		低
    ,		G_WARN_T_CODE_NBPAIRERR									//  *无创血压放气错误	血压测量时放气出现问题		低
    ,		G_WARN_T_CODE_NBPWEAK										//  *无创血压信号太弱	血压测量时脉搏信号太弱，无法计算出血压		低
    ,		G_WARN_T_CODE_NBPEXD					  					//  *无创血压测量超界	血压测量时血压或脉搏信号超出正常范围，无法进行测量		低
    ,		G_WARN_T_CODE_NBPMOVE										//  *无创血压手臂运动	病人手臂运动		低
    ,		G_WARN_T_CODE_NBPOVERPRESSURE						//  * * 无创血压过压	压力值超过测量范围		低
    ,		G_WARN_T_CODE_NBPSAT					  					//  *无创血压信号饱和	血压测量时脉搏信号超出正常范围，无法进行测量		低
    ,		G_WARN_T_CODE_NBPLEAKCKFAIL							  					//  *无创血压漏气检测失败	袖带未连接好或气路漏气		低
    ,		G_WARN_T_CODE_NBPFAIL										//  * * 无创血压系统错误	血压系统自检失败，一般是压力传感器实效导致自检失败		低
    ,		G_WARN_T_CODE_NBPTIMEOUT			  					//  * * 无创血压测量超时	血压测量超时		低
    ,		G_WARN_T_CODE_NBPTIEERR							  					//  * * 无创血压袖带类型错	病人类型为成人时使用了新生儿袖带		低
    ,		G_WARN_T_CODE_NBPMESSUREFAIL		  					//  * * 无创血压测量失败	本次血压测量未能计算出血压		低
    ,		G_WARN_T_CODE_NBPRESETERR							  					//  * * 无创血压非法复位	血压测量时异常复位		低
    ,		G_WARN_T_CODE_CO2STANDBY								 			//  * * CO₂待命	CO₂处于待命状态		低
    ,		G_WARN_T_CODE_CO2STOP							  					//  * * *CO₂通讯停止	CO₂模块和主机通讯出现问题		低

};
*/
QString g_WarningName[] = {
    "no warning"
    ,        G_WARN_P_TXT_ASYSTOLE       //高	//超过4秒钟无心跳信号
    , 		G_WARN_P_TXT_APNEA              //高	//超过设定的呼吸窒息时间无呼吸信号
    , 		G_WARN_P_TXT_NOPULSE        //高	//超过15秒无脉搏信号
    , 		G_WARN_P_TXT_HRHIGH         //高	//心率超过报警高限
    , 		G_WARN_P_TXT_HRHLOW     //高	//心率低于报警低限
    , 		G_WARN_P_TXT_ST1HIGH        //高	//I导联ST值超过报警高限
    , 		G_WARN_P_TXT_ST1LOW         //高	//I导联ST值低于报警低限
    , 		G_WARN_P_TXT_ST2HIGH        //高	//II导联ST值超过报警高限
    , 		G_WARN_P_TXT_ST2LOW         //高	//II导联ST值低于报警低限
    , 		G_WARN_P_TXT_ST3HIGH            //高	//III导联ST值超过报警高限
    , 		G_WARN_P_TXT_ST3LOW         //高	//III导联ST值低于报警低限
    , 		G_WARN_P_TXT_STAVRHIGH      //高	//AVR导联ST值超过报警高限
    , 		G_WARN_P_TXT_STAVRLOW           //高	//AVR导联ST值低于报警低限
    , 		G_WARN_P_TXT_STAVLHIGH          //高	//AVL导联ST值超过报警高限
    , 		G_WARN_P_TXT_STAVLLOW           //高	//AVL导联ST值低于报警低限
    , 		G_WARN_P_TXT_STAVFHIGH          //高	//AVF导联ST值超过报警高限
    , 		G_WARN_P_TXT_STAVFLOW           //高	//AVF导联ST值低于报警低限
    , 		G_WARN_P_TXT_STVHIGH            //高	//V导联ST值超过报警高限
    , 		G_WARN_P_TXT_STVLOW         //高	//V导联ST值低于报警低限
    , 		G_WARN_P_TXT_PVCHIGH            //高	//PVCs值超过报警高限
    , 		G_WARN_P_TXT_SPO2HIGH           //中	//氧饱和度超过报警高限
    , 		G_WARN_P_TXT_SPO2LOW            //中	//氧饱和度低于报警低限
    , 		G_WARN_P_TXT_PRHIGH         //中	//脉率超过报警高限
    , 		G_WARN_P_TXT_PRLOW          //中	//脉率低于报警低限
    , 		G_WARN_P_TXT_NSHIGH         //中	//收缩压超过报警高限
    , 		G_WARN_P_TXT_NSLOW          //中	//收缩压低于报警低限
    , 		G_WARN_P_TXT_NMHIGH         //中	//平均压超过报警高限
    , 		G_WARN_P_TXT_NMLOW          //中	//平均压低于报警低限
    , 		G_WARN_P_TXT_NDHIGH         //中	//舒张压超过报警高限
    , 		G_WARN_P_TXT_NDLOW          //中	//舒张压低于报警低限
    , 		G_WARN_P_TXT_RRHIGH         //中	//呼吸率超过报警高限
    , 		G_WARN_P_TXT_RRLOW          //中	//呼吸率低于报警低限
    , 		G_WARN_P_TXT_TEMP1HIGH          //中	//体温通道1超过报警高限
    , 		G_WARN_P_TXT_TEMP1LOW           //中	//体温通道1低于报警低限
    , 		G_WARN_P_TXT_TEMP2HIGH          //中	//体温通道2超过报警高限
    , 		G_WARN_P_TXT_TEMP2LOW           //中	//体温通道2低于报警低限
    , 		G_WARN_P_TXT_IBP1NSHIGH         //中	//主动脉收缩压超过报警高限
    , 		G_WARN_P_TXT_IBP1NSLOW          //中	//主动脉收缩压低于报警低限
    , 		G_WARN_P_TXT_IBP1NMHIGH         //中	//主动脉平均压超过报警高限
    , 		G_WARN_P_TXT_IBP1NMLOW											//中	//主动脉平均压低于报警低限
    , 		G_WARN_P_TXT_IBP1NDHIGH		//中	//主动脉舒张压超过报警高限
    , 		G_WARN_P_TXT_IBP1NDLOW		//中	//肺动脉舒张压低于报警低限
    , 		G_WARN_P_TXT_IBP2NSHIGH		//中	//肺动脉收缩压超过报警高限
    , 		G_WARN_P_TXT_IBP2NSLOW		//中	//肺动脉收缩压低于报警低限
    , 		G_WARN_P_TXT_IBP2NMHIGH		//中	//肺动脉平均压超过报警高限
    , 		G_WARN_P_TXT_IBP2NMLOW		//中	//肺动脉平均压低于报警低限
    , 		G_WARN_P_TXT_IBP2NDHIGH		//中	//肺动脉舒张压超过报警高限
    , 		G_WARN_P_TXT_IBP2NDLOW		//中	//肺动脉舒张压低于报警低限
    , 		G_WARN_P_TXT_IBP3NSHIGH		//中	//中心静脉收缩压超过报警高限
    , 		G_WARN_P_TXT_IBP3NSLOW		//中	//中心静脉收缩压低于报警低限
    , 		G_WARN_P_TXT_IBP3NMHIGH		//中	//中心静脉平均压超过报警高限
    , 		G_WARN_P_TXT_IBP3NMLOW		//中	//中心静脉平均压低于报警低限
    , 		G_WARN_P_TXT_IBP3NDHIGH		//中	//中心静脉舒张压超过报警高限
    , 		G_WARN_P_TXT_IBP3NDLOW		//中	//中心静脉舒张压低于报警低限
    , 		G_WARN_P_TXT_IBP4NSHIGH		  									//中	//左房收缩压超过报警高限
    , 		G_WARN_P_TXT_IBP4NSLOW		  									//中	//左房收缩压低于报警低限
    , 		G_WARN_P_TXT_IBP4NMHIGH			  									//中	//左房平均压超过报警高限
    , 		G_WARN_P_TXT_IBP4NMLOW		  									//中	//左房平均压低于报警低限
    , 		G_WARN_P_TXT_IBP4NDHIGH			  									//中	//左房舒张压超过报警高限
    , 		G_WARN_P_TXT_IBP4NDLOW		  									//中	//左房舒张压低于报警低限
    , 		G_WARN_P_TXT_IBP5NSHIGH			  									//中	//右房收缩压超过报警高限
    , 		G_WARN_P_TXT_IBP5NSLOW		  									//中	//右房收缩压低于报警低限
    , 		G_WARN_P_TXT_IBP5NMHIGH			  									//中	//右房平均压超过报警高限
    , 		G_WARN_P_TXT_IBP5NMLOW		  									//中	//右房平均压低于报警低限
    , 		G_WARN_P_TXT_IBP5NDHIGH			  									//中	//右房舒张压超过报警高限
    , 		G_WARN_P_TXT_IBP5NDLOW		  									//中	//右房舒张压低于报警低限
    , 		G_WARN_P_TXT_IBP6NSHIGH			  									//中	//颅内收缩压超过报警高限
    , 		G_WARN_P_TXT_IBP6NSLOW		  									//中	//颅内收缩压低于报警低限
    , 		G_WARN_P_TXT_IBP6NMHIGH			  									//中	//颅内平均压超过报警高限
    , 		G_WARN_P_TXT_IBP6NMLOW		  									//高	//颅内平均压低于报警低限
    , 		G_WARN_P_TXT_IBP6NDHIGH			  									//高	//颅内舒张压超过报警高限
    , 		G_WARN_P_TXT_IBP6NDLOW		  									//高	//颅内舒张压低于报警低限
    , 		G_WARN_P_TXT_IBP7NSHIGH			   									//高	//P1收缩压超过报警高限
    , 		G_WARN_P_TXT_IBP7NSLOW		   									//高	//P1收缩压低于报警低限
    , 		G_WARN_P_TXT_IBP7NMHIGH			   									//高	//P1平均压超过报警高限
    , 		G_WARN_P_TXT_IBP7NMLOW		 									//高	//P1平均压低于报警低限
    , 		G_WARN_P_TXT_IBP7NDHIGH			   									//高	//P1舒张压超过报警高限
    , 		G_WARN_P_TXT_IBP7NDLOW		   									//高	//P1舒张压低于报警低限
    , 		G_WARN_P_TXT_IBP8NSHIGH			    									//高	//P2收缩压超过报警高限
    , 		G_WARN_P_TXT_IBP8NSLOW		    									//高	//P2收缩压低于报警低限
    , 		G_WARN_P_TXT_IBP8NMHIGH			   									//高	//P2平均压超过报警高限
    , 		G_WARN_P_TXT_IBP8NMLOW		   									//高	//P2平均压低于报警低限
    , 		G_WARN_P_TXT_IBP8NDHIGH			  									//高	//P2舒张压超过报警高限
    , 		G_WARN_P_TXT_IBP8NDLOW		   									//高	//P2舒张压低于报警低限
    , 		G_WARN_P_TXT_ETCO2HIGH		   									//中	//呼末CO₂超过报警高限
    , 		G_WARN_P_TXT_ETCO2LOW		   									//中	//呼末CO₂低于报警低限
    , 		G_WARN_P_TXT_FICO2HIGH		   									//中	//吸末CO₂超过报警高限
    , 		G_WARN_P_TXT_FICO2LOW		  									//中	//吸末CO₂低于报警低限
    , 		G_WARN_P_TXT_SPHIGH		   									//中	//气道呼吸率超过报警高限
    , 		G_WARN_P_TXT_SPLOW		   									//中	//气道呼吸率低于报警低限
    , 		G_WARN_T_TXT_ECGLEADOFF		   			//低	//RL或2个以上的心电导联脱落
    , 		G_WARN_T_TXT_RALEADOFF		  			//低	//RA导联脱落
    , 		G_WARN_T_TXT_LALEADOFF		  			//低	//LA导联脱落
    , 		G_WARN_T_TXT_LLLEADOFF		  			//低	//LL导联脱落
    , 		G_WARN_T_TXT_VLEADOFF		   			//低	//V导联脱落
    , 		G_WARN_T_TXT_MODUINITERR	    			//低	//模块自检错误
    , 		G_WARN_T_TXT_COMMSTOP		   			//低	//模块和主机通讯出现问题
    , 		G_WARN_T_TXT_COMMERR		     			//低	//模块和主机通讯出现问题
    , 		G_WARN_T_TXT_WARNLIMITERR		    			//低	//参数的报警限被意外改动
    , 		G_WARN_T_TXT_PARALIMITERR		    			//低	//参数的测量值超出了系统所能进行的测量范围
    , 		G_WARN_T_TXT_SPO2SENSER		    			//低	//血氧探头未接好
    , 		G_WARN_T_TXT_SPO2FINGER		  			//低	//手指从血氧探头中脱落
    , 		G_WARN_T_TXT_SEARCHPULSE	  			//低	//血氧探头没有连接好或病人运动手臂
    , 		G_WARN_T_TXT_TEMP1SENSOR		 			//低	//体温通道1探头未接好
    , 		G_WARN_T_TXT_TEMP2SENSOR		 			//低	//体温通道2探头未接好
    , 		G_WARN_T_TXT_WATCHDOGERR	     			//低	//主机看门狗自检失败
    , 		G_WARN_T_TXT_SYSTIMEERR	    			//低	//系统时钟未设置
    , 		G_WARN_T_TXT_12VHIGH	  			//低	//12V电压检测超出正常电压范围
    , 		G_WARN_T_TXT_12VLOW	  			//低	//12V电压检测低于正常电压范围
    , 		G_WARN_T_TXT_3_3VHIGH	  			//低	//3.3V电压检测超出正常电压范围
    , 		G_WARN_T_TXT_3_3VLOW	  			//低	//3.3V电压检测低于正常电压范围
    , 		G_WARN_T_TXT_BATHIGH	    			//低	//电池电压检测超出正常电压范围
    , 		G_WARN_T_TXT_BATLOW					//低	//电池电量不足
    , 		G_WARN_T_TXT_TIELOOSE	    			//低	//袖带未连接好
    , 		G_WARN_T_TXT_NBPLEAK		     			//低	//袖带未连接好或气路漏气
    , 		G_WARN_T_TXT_NBPAIRERR		   			//低	//血压测量时放气出现问题
    , 		G_WARN_T_TXT_NBPWEAK		   			//低	//血压测量时脉搏信号太弱，无法计算出血压
    , 		G_WARN_T_TXT_NBPEXD		   			//低	//血压测量时血压或脉搏信号超出正常范围，无法进行测量
    , 		G_WARN_T_TXT_NBPMOVE		   			//低	//病人手臂运动
    , 		G_WARN_T_TXT_NBPOVERPRESSURE		    			//低	//压力值超过测量范围
    , 		G_WARN_T_TXT_NBPSAT		   			//低	//血压测量时脉搏信号超出正常范围，无法进行测量
    , 		G_WARN_T_TXT_NBPLEAKCKFAIL 			//低	//袖带未连接好或气路漏气
    , 		G_WARN_T_TXT_NBPFAIL		  			//低	//血压系统自检失败，一般是压力传感器实效导致自检失败
    , 		G_WARN_T_TXT_NBPTIMEOUT		  			//低	//血压测量超时
    , 		G_WARN_T_TXT_NBPTIEERR	 			//低	//病人类型为成人时使用了新生儿袖带
    , 		G_WARN_T_TXT_NBPMESSUREFAIL 	  			//低	//本次血压测量未能计算出血压
    , 		G_WARN_T_TXT_NBPRESETERR	  			//低	//血压测量时异常复位
    , 		G_WARN_T_TXT_CO2STANDBY	     			//低	//CO₂处于待命状态
    , 		G_WARN_T_TXT_CO2STOP		  			//低	//CO₂模块和主机通讯出现问题
    ,       G_WARN_T_TXT_HEARTV
    ,       G_WARN_T_TXT_STARTVOICE

};
QString g_WarningFile[] = {
    G_WARN_NO_WARNING
    ,        G_WARN_P_FILE_ASYSTOLE       //高	//超过4秒钟无心跳信号
    , 		G_WARN_P_FILE_APNEA              //高	//超过设定的呼吸窒息时间无呼吸信号
    , 		G_WARN_P_FILE_NOPULSE        //高	//超过15秒无脉搏信号
    , 		G_WARN_P_FILE_HRHIGH         //高	//心率超过报警高限
    , 		G_WARN_P_FILE_HRHLOW     //高	//心率低于报警低限
    , 		G_WARN_P_FILE_ST1HIGH        //高	//I导联ST值超过报警高限
    , 		G_WARN_P_FILE_ST1LOW         //高	//I导联ST值低于报警低限
    , 		G_WARN_P_FILE_ST2HIGH        //高	//II导联ST值超过报警高限
    , 		G_WARN_P_FILE_ST2LOW         //高	//II导联ST值低于报警低限
    , 		G_WARN_P_FILE_ST3HIGH            //高	//III导联ST值超过报警高限
    , 		G_WARN_P_FILE_ST3LOW         //高	//III导联ST值低于报警低限
    , 		G_WARN_P_FILE_STAVRHIGH      //高	//AVR导联ST值超过报警高限
    , 		G_WARN_P_FILE_STAVRLOW           //高	//AVR导联ST值低于报警低限
    , 		G_WARN_P_FILE_STAVLHIGH          //高	//AVL导联ST值超过报警高限
    , 		G_WARN_P_FILE_STAVLLOW           //高	//AVL导联ST值低于报警低限
    , 		G_WARN_P_FILE_STAVFHIGH          //高	//AVF导联ST值超过报警高限
    , 		G_WARN_P_FILE_STAVFLOW           //高	//AVF导联ST值低于报警低限
    , 		G_WARN_P_FILE_STVHIGH            //高	//V导联ST值超过报警高限
    , 		G_WARN_P_FILE_STVLOW         //高	//V导联ST值低于报警低限
    , 		G_WARN_P_FILE_PVCHIGH            //高	//PVCs值超过报警高限
    , 		G_WARN_P_FILE_SPO2HIGH           //中	//氧饱和度超过报警高限
    , 		G_WARN_P_FILE_SPO2LOW            //中	//氧饱和度低于报警低限
    , 		G_WARN_P_FILE_PRHIGH         //中	//脉率超过报警高限
    , 		G_WARN_P_FILE_PRLOW          //中	//脉率低于报警低限
    , 		G_WARN_P_FILE_NSHIGH         //中	//收缩压超过报警高限
    , 		G_WARN_P_FILE_NSLOW          //中	//收缩压低于报警低限
    , 		G_WARN_P_FILE_NMHIGH         //中	//平均压超过报警高限
    , 		G_WARN_P_FILE_NMLOW          //中	//平均压低于报警低限
    , 		G_WARN_P_FILE_NDHIGH         //中	//舒张压超过报警高限
    , 		G_WARN_P_FILE_NDLOW          //中	//舒张压低于报警低限
    , 		G_WARN_P_FILE_RRHIGH         //中	//呼吸率超过报警高限
    , 		G_WARN_P_FILE_RRLOW          //中	//呼吸率低于报警低限
    , 		G_WARN_P_FILE_TEMP1HIGH          //中	//体温通道1超过报警高限
    , 		G_WARN_P_FILE_TEMP1LOW           //中	//体温通道1低于报警低限
    , 		G_WARN_P_FILE_TEMP2HIGH          //中	//体温通道2超过报警高限
    , 		G_WARN_P_FILE_TEMP2LOW           //中	//体温通道2低于报警低限
    , 		G_WARN_P_FILE_IBP1NSHIGH         //中	//主动脉收缩压超过报警高限
    , 		G_WARN_P_FILE_IBP1NSLOW          //中	//主动脉收缩压低于报警低限
    , 		G_WARN_P_FILE_IBP1NMHIGH         //中	//主动脉平均压超过报警高限
    , 		G_WARN_P_FILE_IBP1NMLOW											//中	//主动脉平均压低于报警低限
    , 		G_WARN_P_FILE_IBP1NDHIGH		//中	//主动脉舒张压超过报警高限
    , 		G_WARN_P_FILE_IBP1NDLOW		//中	//肺动脉舒张压低于报警低限
    , 		G_WARN_P_FILE_IBP2NSHIGH		//中	//肺动脉收缩压超过报警高限
    , 		G_WARN_P_FILE_IBP2NSLOW		//中	//肺动脉收缩压低于报警低限
    , 		G_WARN_P_FILE_IBP2NMHIGH		//中	//肺动脉平均压超过报警高限
    , 		G_WARN_P_FILE_IBP2NMLOW		//中	//肺动脉平均压低于报警低限
    , 		G_WARN_P_FILE_IBP2NDHIGH		//中	//肺动脉舒张压超过报警高限
    , 		G_WARN_P_FILE_IBP2NDLOW		//中	//肺动脉舒张压低于报警低限
    , 		G_WARN_P_FILE_IBP3NSHIGH		//中	//中心静脉收缩压超过报警高限
    , 		G_WARN_P_FILE_IBP3NSLOW		//中	//中心静脉收缩压低于报警低限
    , 		G_WARN_P_FILE_IBP3NMHIGH		//中	//中心静脉平均压超过报警高限
    , 		G_WARN_P_FILE_IBP3NMLOW		//中	//中心静脉平均压低于报警低限
    , 		G_WARN_P_FILE_IBP3NDHIGH		//中	//中心静脉舒张压超过报警高限
    , 		G_WARN_P_FILE_IBP3NDLOW		//中	//中心静脉舒张压低于报警低限
    , 		G_WARN_P_FILE_IBP4NSHIGH		  									//中	//左房收缩压超过报警高限
    , 		G_WARN_P_FILE_IBP4NSLOW		  									//中	//左房收缩压低于报警低限
    , 		G_WARN_P_FILE_IBP4NMHIGH		  									//中	//左房平均压超过报警高限
    , 		G_WARN_P_FILE_IBP4NMLOW		  									//中	//左房平均压低于报警低限
    , 		G_WARN_P_FILE_IBP4NDHIGH		  									//中	//左房舒张压超过报警高限
    , 		G_WARN_P_FILE_IBP4NDLOW	  									//中	//左房舒张压低于报警低限
    , 		G_WARN_P_FILE_IBP5NSHIGH		  									//中	//右房收缩压超过报警高限
    , 		G_WARN_P_FILE_IBP5NSLOW		  									//中	//右房收缩压低于报警低限
    , 		G_WARN_P_FILE_IBP5NMHIGH		  									//中	//右房平均压超过报警高限
    , 		G_WARN_P_FILE_IBP5NMLOW		  									//中	//右房平均压低于报警低限
    , 		G_WARN_P_FILE_IBP5NDHIGH		  									//中	//右房舒张压超过报警高限
    , 		G_WARN_P_FILE_IBP5NDLOW		  									//中	//右房舒张压低于报警低限
    , 		G_WARN_P_FILE_IBP6NSHIGH		  									//中	//颅内收缩压超过报警高限
    , 		G_WARN_P_FILE_IBP6NSLOW		  									//中	//颅内收缩压低于报警低限
    , 		G_WARN_P_FILE_IBP6NMHIGH		  									//中	//颅内平均压超过报警高限
    , 		G_WARN_P_FILE_IBP6NMLOW		  									//高	//颅内平均压低于报警低限
    , 		G_WARN_P_FILE_IBP6NDHIGH		  									//高	//颅内舒张压超过报警高限
    , 		G_WARN_P_FILE_IBP6NDLOW		  									//高	//颅内舒张压低于报警低限
    , 		G_WARN_P_FILE_IBP7NSHIGH		   									//高	//P1收缩压超过报警高限
    , 		G_WARN_P_FILE_IBP7NSLOW		   									//高	//P1收缩压低于报警低限
    , 		G_WARN_P_FILE_IBP7NMHIGH		   									//高	//P1平均压超过报警高限
    , 		G_WARN_P_FILE_IBP7NMLOW		 									//高	//P1平均压低于报警低限
    , 		G_WARN_P_FILE_IBP7NDHIGH		   									//高	//P1舒张压超过报警高限
    , 		G_WARN_P_FILE_IBP7NDLOW		   									//高	//P1舒张压低于报警低限
    , 		G_WARN_P_FILE_IBP8NSHIGH		    									//高	//P2收缩压超过报警高限
    , 		G_WARN_P_FILE_IBP8NSLOW		    									//高	//P2收缩压低于报警低限
    , 		G_WARN_P_FILE_IBP8NMHIGH		   									//高	//P2平均压超过报警高限
    , 		G_WARN_P_FILE_IBP8NMLOW	   									//高	//P2平均压低于报警低限
    , 		G_WARN_P_FILE_IBP8NDHIGH		  									//高	//P2舒张压超过报警高限
    , 		G_WARN_P_FILE_IBP8NDLOW		   									//高	//P2舒张压低于报警低限
    , 		G_WARN_P_FILE_ETCO2HIGH		   									//中	//呼末CO₂超过报警高限
    , 		G_WARN_P_FILE_ETCO2LOW		   									//中	//呼末CO₂低于报警低限
    , 		G_WARN_P_FILE_FICO2HIGH		   									//中	//吸末CO₂超过报警高限
    , 		G_WARN_P_FILE_FICO2LOW		  									//中	//吸末CO₂低于报警低限
    , 		G_WARN_P_FILE_SPHIGH		   									//中	//气道呼吸率超过报警高限
    , 		G_WARN_P_FILE_SPLOW		   									//中	//气道呼吸率低于报警低限
    , 		G_WARN_T_FILE_ECGLEADOFF		   			//低	//RL或2个以上的心电导联脱落
    , 		G_WARN_T_FILE_RALEADOFF		  			//低	//RA导联脱落
    , 		G_WARN_T_FILE_LALEADOFF		  			//低	//LA导联脱落
    , 		G_WARN_T_FILE_LLLEADOFF		  			//低	//LL导联脱落
    , 		G_WARN_T_FILE_VLEADOFF		   			//低	//V导联脱落
    , 		G_WARN_T_FILE_MODUINITERR	    			//低	//模块自检错误
    , 		G_WARN_T_FILE_COMMSTOP		   			//低	//模块和主机通讯出现问题
    , 		G_WARN_T_FILE_COMMERR		     			//低	//模块和主机通讯出现问题
    , 		G_WARN_T_FILE_WARNLIMITERR		    			//低	//参数的报警限被意外改动
    , 		G_WARN_T_FILE_PARALIMITERR		    			//低	//参数的测量值超出了系统所能进行的测量范围
    , 		G_WARN_T_FILE_SPO2SENSER		    			//低	//血氧探头未接好
    , 		G_WARN_T_FILE_SPO2FINGER		  			//低	//手指从血氧探头中脱落
    , 		G_WARN_T_FILE_SEARCHPULSE	  			//低	//血氧探头没有连接好或病人运动手臂
    , 		G_WARN_T_FILE_TEMP1SENSOR		 			//低	//体温通道1探头未接好
    , 		G_WARN_T_FILE_TEMP2SENSOR		 			//低	//体温通道2探头未接好
    , 		G_WARN_T_FILE_WATCHDOGERR	     			//低	//主机看门狗自检失败
    , 		G_WARN_T_FILE_SYSTIMEERR	    			//低	//系统时钟未设置
    , 		G_WARN_T_FILE_12VHIGH	  			//低	//12V电压检测超出正常电压范围
    , 		G_WARN_T_FILE_12VLOW	  			//低	//12V电压检测低于正常电压范围
    , 		G_WARN_T_FILE_3_3VHIGH	  			//低	//3.3V电压检测超出正常电压范围
    , 		G_WARN_T_FILE_3_3VLOW	  			//低	//3.3V电压检测低于正常电压范围
    , 		G_WARN_T_FILE_BATHIGH	    			//低	//电池电压检测超出正常电压范围
    , 		G_WARN_T_FILE_BATLOW					//低	//电池电量不足
    , 		G_WARN_T_FILE_TIELOOSE	    			//低	//袖带未连接好
    , 		G_WARN_T_FILE_NBPLEAK		     			//低	//袖带未连接好或气路漏气
    , 		G_WARN_T_FILE_NBPAIRERR		   			//低	//血压测量时放气出现问题
    , 		G_WARN_T_FILE_NBPWEAK		   			//低	//血压测量时脉搏信号太弱，无法计算出血压
    , 		G_WARN_T_FILE_NBPEXD		   			//低	//血压测量时血压或脉搏信号超出正常范围，无法进行测量
    , 		G_WARN_T_FILE_NBPMOVE		   			//低	//病人手臂运动
    , 		G_WARN_T_FILE_NBPOVERPRESSURE		    			//低	//压力值超过测量范围
    , 		G_WARN_T_FILE_NBPSAT		   			//低	//血压测量时脉搏信号超出正常范围，无法进行测量
    , 		G_WARN_T_FILE_NBPLEAKCKFAIL 			//低	//袖带未连接好或气路漏气
    , 		G_WARN_T_FILE_NBPFAIL		  			//低	//血压系统自检失败，一般是压力传感器实效导致自检失败
    , 		G_WARN_T_FILE_NBPTIMEOUT		  			//低	//血压测量超时
    , 		G_WARN_T_FILE_NBPTIEERR	 			//低	//病人类型为成人时使用了新生儿袖带
    , 		G_WARN_T_FILE_NBPMESSUREFAIL 	  			//低	//本次血压测量未能计算出血压
    , 		G_WARN_T_FILE_NBPRESETERR	  			//低	//血压测量时异常复位
    , 		G_WARN_T_FILE_CO2STANDBY	     			//低	//CO₂处于待命状态
    , 		G_WARN_T_FILE_CO2STOP		  			//低	//CO₂模块和主机通讯出现问题
    ,       G_WARN_T_FILE_HEARTV
    ,       G_WARN_T_FILE_STARTVOICE
};
 int g_WarningPri[]={
     0xff
    ,G_WARN_PRIORITY_HIGH//		G_WARN_P_CODE_ASYSTOLE				0x1 			//  * * *心脏停搏	超过4秒钟无心跳信号	高
    , G_WARN_PRIORITY_HIGH//		G_WARN_P_CODE_APNEA						0x2 			//  * * *呼吸窒息	超过设定的呼吸窒息时间无呼吸信号	高
    , G_WARN_PRIORITY_HIGH//		G_WARN_P_CODE_NOPULSE				0x3 			//  * * *无脉搏	超过15秒无脉搏信号	高
    , G_WARN_PRIORITY_HIGH//		G_WARN_P_CODE_HRHIGH					0x4 			//  * * 心率太高	心率超过报警高限	高
    , G_WARN_PRIORITY_HIGH//		G_WARN_P_CODE_HRLOW					0x5 			//  * * 心率太低	心率低于报警低限	高
    , G_WARN_PRIORITY_HIGH//		G_WARN_P_CODE_ST1HIGH					0x6 			//  * * ST-I太高	I导联ST值超过报警高限	高
    , G_WARN_PRIORITY_HIGH//		G_WARN_P_CODE_ST1LOW					0x7 			//  * * ST-I太低	I导联ST值低于报警低限	高
    , G_WARN_PRIORITY_HIGH//		G_WARN_P_CODE_ST2HIGH					0x8 			//  * * ST-II太高	II导联ST值超过报警高限	高
    ,G_WARN_PRIORITY_HIGH //		G_WARN_P_CODE_ST2LOW					0x9 			//  * * ST-II太低	II导联ST值低于报警低限	高
    , G_WARN_PRIORITY_HIGH//		G_WARN_P_CODE_ST3HIGH					0xA 			//  * * ST-III太高	III导联ST值超过报警高限	高
    , G_WARN_PRIORITY_HIGH//		G_WARN_P_CODE_ST3LOW					0xB 			//  * * ST-III太低	III导联ST值低于报警低限	高
    , G_WARN_PRIORITY_HIGH//		G_WARN_P_CODE_STAVRHIGH	  		0xC 			//  * * ST-AVR太高	AVR导联ST值超过报警高限	高
    , G_WARN_PRIORITY_HIGH//		G_WARN_P_CODE_STAVRLOW	  		0xD 			//  * * ST-AVR太低	AVR导联ST值低于报警低限	高
    ,G_WARN_PRIORITY_HIGH //		G_WARN_P_CODE_STAVLHIGH	  		0xE 			//  * * ST-AVL太高	AVL导联ST值超过报警高限	高
    , G_WARN_PRIORITY_HIGH//		G_WARN_P_CODE_STAVLLOW	  		0xF 			//  * * ST-AVL太低	AVL导联ST值低于报警低限	高
    , G_WARN_PRIORITY_HIGH//		G_WARN_P_CODE_STAVFHIGH				0x10			//  * * ST-AVF太高	AVF导联ST值超过报警高限	高
    , G_WARN_PRIORITY_HIGH//		G_WARN_P_CODE_STAVFLOW	  		0x11			//  * * ST-AVF太低	AVF导联ST值低于报警低限	高
    ,G_WARN_PRIORITY_HIGH //		G_WARN_P_CODE_STVHIGH	    		0x12			//  * * ST-V太高	V导联ST值超过报警高限	高
    ,G_WARN_PRIORITY_HIGH //		G_WARN_P_CODE_STVLOW		  		0x13			//  * * ST-V太低	V导联ST值低于报警低限	高
    ,G_WARN_PRIORITY_HIGH //		G_WARN_P_CODE_PVCHIGH	    		0x14			//  * * PVCs太高	PVCs值超过报警高限	高
    ,G_WARN_PRIORITY_MID //		G_WARN_P_CODE_SPO2HIGH	  		0x15			//  * * 氧饱和度太高	氧饱和度超过报警高限	中
    , G_WARN_PRIORITY_MID//		G_WARN_P_CODE_SPO2LOW		  		0x16			//  * * 氧饱和度太低	氧饱和度低于报警低限	中
    , G_WARN_PRIORITY_MID//		G_WARN_P_CODE_PRHIGH		  		0x17			//  * * 脉率太高	脉率超过报警高限	中
    , G_WARN_PRIORITY_MID//		G_WARN_P_CODE_PRLOW			  		0x18			//  * * 脉率太低	脉率低于报警低限	中
    , G_WARN_PRIORITY_MID//		G_WARN_P_CODE_NSHIGH					0x19			//  * * 收缩压太高	收缩压超过报警高限	中
    , G_WARN_PRIORITY_MID//		G_WARN_P_CODE_NSLOW						0x1A			//  * * 收缩压太低	收缩压低于报警低限	中
    , G_WARN_PRIORITY_MID//		G_WARN_P_CODE_NMHIGH					0x1B			//  * * 平均压太高	平均压超过报警高限	中
    ,G_WARN_PRIORITY_MID //		G_WARN_P_CODE_NMLOW						0x1C			//  * * 平均压太低	平均压低于报警低限	中
    , G_WARN_PRIORITY_MID//		G_WARN_P_CODE_NDHIGH					0x1D			//  * * 舒张压太高	舒张压超过报警高限	中
    ,G_WARN_PRIORITY_MID //		G_WARN_P_CODE_NDLOW						0x1E			//  * * 舒张压太低	舒张压低于报警低限	中
    , G_WARN_PRIORITY_MID//		G_WARN_P_CODE_RRHIGH					0x1F			//  * * 呼吸率太高	呼吸率超过报警高限	中
    , G_WARN_PRIORITY_MID//		G_WARN_P_CODE_RRLOW						0x20			//  * * 呼吸率太低	呼吸率低于报警低限	中
    , G_WARN_PRIORITY_MID//		G_WARN_P_CODE_TEMP1HIGH	  		0x21			//  * * 体温通道1太高	体温通道1超过报警高限	中
    , G_WARN_PRIORITY_MID//		G_WARN_P_CODE_TEMP1LOW	  		0x22			//  * * 体温通道1太低	体温通道1低于报警低限	中
    ,G_WARN_PRIORITY_MID //		G_WARN_P_CODE_TEMP2HIGH	  		0x23			//  * * 体温通道2太高	体温通道2超过报警高限	中
    , G_WARN_PRIORITY_MID//		G_WARN_P_CODE_TEMP2LOW	  		0x24			//  * * 体温通道2太低	体温通道2低于报警低限	中
    , G_WARN_PRIORITY_MID//		G_WARN_P_CODE_IBP1NSHIGH	        		0x25			//  * * 主动脉压收缩压太高	主动脉收缩压超过报警高限	中
    , G_WARN_PRIORITY_MID//		G_WARN_P_CODE_IBP1NSLOW	        		0x26			//  * * 主动脉压收缩压太低	主动脉收缩压低于报警低限	中
    , G_WARN_PRIORITY_MID//		G_WARN_P_CODE_IBP1NMHIGH	        		0x27			//  * * 主动脉压平均压太高	主动脉平均压超过报警高限	中
    , G_WARN_PRIORITY_MID//		G_WARN_P_CODE_IBP1NMLOW		        		0x28			//  * * 主动脉压平均压太低	主动脉平均压低于报警低限	中
    , G_WARN_PRIORITY_MID//		G_WARN_P_CODE_IBP1NDHIGH	        		0x29			//  * * 主动脉压舒张压太高	主动脉舒张压超过报警高限	中
    ,G_WARN_PRIORITY_MID //		G_WARN_P_CODE_IBP1NDLOW	        		0x2A			//  * * 肺动脉压舒张压太低	肺动脉舒张压低于报警低限	中
    , G_WARN_PRIORITY_MID//		G_WARN_P_CODE_IBP2NSHIGH	        		0x2B			//  * * 肺动脉压收缩压太高	肺动脉收缩压超过报警高限	中
    , G_WARN_PRIORITY_MID//		G_WARN_P_CODE_IBP2NSLOW		        		0x2C			//  * * 肺动脉压收缩压太低	肺动脉收缩压低于报警低限	中
    , G_WARN_PRIORITY_MID//		G_WARN_P_CODE_IBP2NMHIGH	        		0x2D			//  * * 肺动脉压平均压太高	肺动脉平均压超过报警高限	中
    , G_WARN_PRIORITY_MID//		G_WARN_P_CODE_IBP2NMLOW	        		0x2E			//  * * 肺动脉压平均压太低	肺动脉平均压低于报警低限	中
    , G_WARN_PRIORITY_MID//		G_WARN_P_CODE_IBP2NDHIGH	        		0x2F			//  * * 肺动脉压舒张压太高	肺动脉舒张压超过报警高限	中
    , G_WARN_PRIORITY_MID//		G_WARN_P_CODE_IBP2NDLOW	        		0x30			//  * * 肺动脉压舒张压太低	肺动脉舒张压低于报警低限	中
    , G_WARN_PRIORITY_MID//		G_WARN_P_CODE_IBP3NSHIGH	        		0x32			//  * * 中心静脉压收缩压太高	中心静脉收缩压超过报警高限	中
    , G_WARN_PRIORITY_MID//		G_WARN_P_CODE_IBP3NSLOW	        		0x33			//  * * 中心静脉压收缩压太低	中心静脉收缩压低于报警低限	中
    , G_WARN_PRIORITY_MID//		G_WARN_P_CODE_IBP3NMHIGH	        		0x34			//  * * 中心静脉压平均压太高	中心静脉平均压超过报警高限	中
    , G_WARN_PRIORITY_MID//		G_WARN_P_CODE_IBP3NMLOW	        		0x35			//  * * 中心静脉压平均压太低	中心静脉平均压低于报警低限	中
    , G_WARN_PRIORITY_MID//		G_WARN_P_CODE_IBP3NDHIGH	        		0x36			//  * * 中心静脉压舒张压太高	中心静脉舒张压超过报警高限	中
    , G_WARN_PRIORITY_MID//		G_WARN_P_CODE_IBP3NDLOW	        		0x37			//  * * 中心静脉压舒张压太低	中心静脉舒张压低于报警低限	中
    ,		G_WARN_PRIORITY_MID		        	//	0x38			//  * * 左房压收缩压太高	左房收缩压超过报警高限	中
    ,		G_WARN_PRIORITY_MID		        		//0x39			//  * * 左房压收缩压太低	左房收缩压低于报警低限	中
    ,		G_WARN_PRIORITY_MID		        	//	0x3A			//  * * 左房压平均压太高	左房平均压超过报警高限	中
    ,		G_WARN_PRIORITY_MID		        		//0//x3B			//  * * 左房压平均压太低	左房平均压低于报警低限	中
    ,		G_WARN_PRIORITY_MID		        	//	0x3C			//  * * 左房压舒张压太高	左房舒张压超过报警高限	中
    ,		G_WARN_PRIORITY_MID		        		//0x3D			//  * * 左房压舒张压太低	左房舒张压低于报警低限	中
    ,		G_WARN_PRIORITY_MID		        	//	0x3E			//  * * 右房压收缩压太高	右房收缩压超过报警高限	中
    ,		G_WARN_PRIORITY_MID		        		//0x3F			//  * * 右房压收缩压太低	右房收缩压低于报警低限	中
    ,		G_WARN_PRIORITY_MID		        	//	0x40			//  * * 右房压平均压太高	右房平均压超过报警高限	中
    ,		G_WARN_PRIORITY_MID		        		//0x41			//  * * 右房压平均压太低	右房平均压低于报警低限	中
    ,		G_WARN_PRIORITY_MID		        	//	0x42			//  * * 右房压舒张压太高	右房舒张压超过报警高限	中
    ,		G_WARN_PRIORITY_MID		        		//0x43			//  * * 右房压舒张压太低	右房舒张压低于报警低限	中
    ,		G_WARN_PRIORITY_MID		        	//	0x44			//  * * 颅内压收缩压太高	颅内收缩压超过报警高限	中
    ,		G_WARN_PRIORITY_MID		        		//0x45			//  * * 颅内压收缩压太低	颅内收缩压低于报警低限	中
    ,		G_WARN_PRIORITY_MID		        	//	0x46			//  * * 颅内压平均压太高	颅内平均压超过报警高限	中
    ,		G_WARN_PRIORITY_MID		        		//0x47			//  * * 颅内压平均压太低	颅内平均压低于报警低限	高
    ,		G_WARN_PRIORITY_MID		        	//	0x48			//  * * 颅内压舒张压太高	颅内舒张压超过报警高限	高
    ,		G_WARN_PRIORITY_MID		        		//0x49			//  * * 颅内压舒张压太低	颅内舒张压低于报警低限	高
    ,		G_WARN_PRIORITY_MID		        	//	0x4A			//  * * P1压太高	P1收缩压超过报警高限	高
    ,		G_WARN_PRIORITY_MID		        		//0x4B			//  * * P1压太低	P1收缩压低于报警低限	高
    ,		G_WARN_PRIORITY_MID		        	//	0x4C			//  * * P1平均压太高	P1平均压超过报警高限	高
    ,		G_WARN_PRIORITY_MID		        		//0x4D			//  * * P1平均压太低	P1平均压低于报警低限	高
    ,		G_WARN_PRIORITY_MID		        	//	0x4E			//  * * P1舒张压太高	P1舒张压超过报警高限	高
    ,		G_WARN_PRIORITY_MID		        		//0x4F			//  * * P1舒张压太低	P1舒张压低于报警低限	高
    ,		G_WARN_PRIORITY_MID		        	//	0x50			//  * * P2压太高	P2收缩压超过报警高限	高
    ,		G_WARN_PRIORITY_MID		        		//0x51			//  * * P2压太低	P2收缩压低于报警低限	高
    ,		G_WARN_PRIORITY_MID		        	//	0x52			//  * * P2平均压太高	P2平均压超过报警高限	高
    ,		G_WARN_PRIORITY_MID		        		//0x53			//  * * P2平均压太低	P2平均压低于报警低限	高
    ,		G_WARN_PRIORITY_MID		        		//0x54			//  * * P2舒张压太高	P2舒张压超过报警高限	高
    ,		G_WARN_PRIORITY_MID		        		//0x55			//  * * P2舒张压太低	P2舒张压低于报警低限	高
    , G_WARN_PRIORITY_MID//		G_WARN_P_CODE_CO2HIGH	0x56			//  * * 呼末CO₂太高	呼末CO₂超过报警高限	中
    ,G_WARN_PRIORITY_MID//		G_WARN_P_CODE_CO2LOW  	0x57			//  * * 呼末CO₂太低	呼末CO₂低于报警低限	中
    ,		G_WARN_PRIORITY_MID		        //		0x58			//  * * 吸末CO₂太高	吸末CO₂超过报警高限	中
    ,		G_WARN_PRIORITY_MID		        //		0x59			//  * * 吸末CO₂太低	吸末CO₂低于报警低限	中
    , G_WARN_PRIORITY_MID//		G_WARN_P_CODE_SPHIGH	        		0x5A			//  * * 气道呼吸率太高	气道呼吸率超过报警高限	中
    , G_WARN_PRIORITY_MID//		G_WARN_P_CODE_SPLOW	        		0x5B  		//  * * 气道呼吸率太低	气道呼吸率低于报警低限	中
    , G_WARN_PRIORITY_LOW//		G_WARN_T_CODE_ECGLEADOFF			  		0x81			//  * * 心电导联脱落	RL或2个以上的心电导联脱落		低
    , G_WARN_PRIORITY_LOW//		G_WARN_T_CODE_RALEADOFF						0x82			//  * * 心电导联RA脱落	RA导联脱落		低
    , G_WARN_PRIORITY_LOW//		G_WARN_T_CODE_LALEADOFF						0x83			//  * * 心电导联LA脱落	LA导联脱落		低
    , G_WARN_PRIORITY_LOW//		G_WARN_T_CODE_LLLEADOFF						0x84			//  * * 心电导联LL脱落	LL导联脱落		低
    , G_WARN_PRIORITY_LOW//		G_WARN_T_CODE_VLEADOFF				  		0x85			//  * * 心电导联V脱落	V导联脱落		低
    , G_WARN_PRIORITY_LOW//		G_WARN_T_CODE_MODUINITERR							  		0x86			//  * * 模块初始化错	模块自检错误		低
    ,G_WARN_PRIORITY_LOW //		G_WARN_T_CODE_COMMSTOP				  		0x87			//  * * *模块通讯停止	模块和主机通讯出现问题		低
    , G_WARN_PRIORITY_LOW//		G_WARN_T_CODE_COMMERR							0x88			//  * * 模块通讯错	模块和主机通讯出现问题		低
   ,		G_WARN_PRIORITY_MID			//					  		0x89			//  * * 参数报警限错	参数的报警限被意外改动		低
  ,		G_WARN_PRIORITY_MID				//				  		0x8A			//  * * 测量范围超界	参数的测量值超出了系统所能进行的测量范围		低
    ,G_WARN_PRIORITY_LOW//		G_WARN_T_CODE_SPO2SENSER			  		0x8B			//  * * 血氧探头脱落	血氧探头未接好		低
    ,G_WARN_PRIORITY_LOW //		G_WARN_T_CODE_SPO2FINGER			  		0x8C			//  * * 血氧探头手指脱落	手指从血氧探头中脱落		低
    ,G_WARN_PRIORITY_LOW //		G_WARN_T_CODE_SEARCHPULSE							  		0x8D			//  * * 搜索脉搏...	血氧探头没有连接好或病人运动手臂		低
    ,G_WARN_PRIORITY_LOW //		G_WARN_T_CODE_TEMP1SENSOR					0x8E			//  * * 体温通道1探头脱落	体温通道1探头未接好		低
    ,G_WARN_PRIORITY_LOW//		G_WARN_T_CODE_TEMP2SENSOR					0x8F			//  * * 体温通道2探头脱落	体温通道2探头未接好		低
    , G_WARN_PRIORITY_LOW//		G_WARN_T_CODE_WATCHDOGERR							  		0x90			//  * * 看门狗错误	主机看门狗自检失败		低
    ,G_WARN_PRIORITY_LOW //		G_WARN_T_CODE_SYSTIMEERR								  		0x91			//  * * 系统时间丢失	系统时钟未设置		低
    , G_WARN_PRIORITY_LOW//		G_WARN_T_CODE_12VHIGH							  		0x92			//  * * 12V电压太高	12V电压检测超出正常电压范围		低
    , G_WARN_PRIORITY_LOW//		G_WARN_T_CODE_12VLOW							  		0x93			//  * * 12V电压太低	12V电压检测低于正常电压范围		低
    ,G_WARN_PRIORITY_LOW //		G_WARN_T_CODE_3_3VHIGH							  		0x94			//  * * 3.3V电压太高	3.3V电压检测超出正常电压范围		低
    ,G_WARN_PRIORITY_LOW //		G_WARN_T_CODE_3_3VLOW							  		0x95			//  * * 3.3V电压太低	3.3V电压检测低于正常电压范围		低
    ,G_WARN_PRIORITY_LOW //		G_WARN_T_CODE_BATHIGH							  		0x96			//  * * 电池电压太高	电池电压检测超出正常电压范围		低
    , G_WARN_PRIORITY_LOW//		G_WARN_T_CODE_BATLOW							  		0x97			//  * * 电池不足，请立即充电	电池电量不足		低
    ,G_WARN_PRIORITY_LOW //		G_WARN_T_CODE_TIELOOSE							  		0x98			//  *无创血压袖带松	袖带未连接好		低
    , G_WARN_PRIORITY_LOW//		G_WARN_T_CODE_NBPLEAK							0x99			//  *无创血压漏气	袖带未连接好或气路漏气		低
    , G_WARN_PRIORITY_LOW//		G_WARN_T_CODE_NBPAIRERR						0x9A			//  *无创血压放气错误	血压测量时放气出现问题		低
    , G_WARN_PRIORITY_LOW//		G_WARN_T_CODE_NBPWEAK							0x9B			//  *无创血压信号太弱	血压测量时脉搏信号太弱，无法计算出血压		低
    ,G_WARN_PRIORITY_LOW //		G_WARN_T_CODE_NBPEXD					  		0x9C			//  *无创血压测量超界	血压测量时血压或脉搏信号超出正常范围，无法进行测量		低
    , G_WARN_PRIORITY_LOW//		G_WARN_T_CODE_NBPMOVE							0x9D			//  *无创血压手臂运动	病人手臂运动		低
    ,G_WARN_PRIORITY_LOW //		G_WARN_T_CODE_NBPOVERPRESSURE			0x9E			//  * * 无创血压过压	压力值超过测量范围		低
    ,G_WARN_PRIORITY_LOW //		G_WARN_T_CODE_NBPSAT					  		0x9F			//  *无创血压信号饱和	血压测量时脉搏信号超出正常范围，无法进行测量		低
    , G_WARN_PRIORITY_LOW//		G_WARN_T_CODE_NBPLEAKCKFAIL							  		0xA0			//  *无创血压漏气检测失败	袖带未连接好或气路漏气		低
    , G_WARN_PRIORITY_LOW//		G_WARN_T_CODE_NBPFAIL							0xA1			//  * * 无创血压系统错误	血压系统自检失败，一般是压力传感器实效导致自检失败		低
    , G_WARN_PRIORITY_LOW//		G_WARN_T_CODE_NBPTIMEOUT			  		0xA2			//  * * 无创血压测量超时	血压测量超时		低
    , G_WARN_PRIORITY_LOW//		G_WARN_T_CODE_NBPTIEERR							  		0xA3			//  * * 无创血压袖带类型错	病人类型为成人时使用了新生儿袖带		低
    , G_WARN_PRIORITY_LOW//		G_WARN_T_CODE_NBPMESSUREFAIL		  		0xA4			//  * * 无创血压测量失败	本次血压测量未能计算出血压		低
    , G_WARN_PRIORITY_LOW//		G_WARN_T_CODE_NBPRESETERR							  		0xA5			//  * * 无创血压非法复位	血压测量时异常复位		低
    ,G_WARN_PRIORITY_LOW //		G_WARN_T_CODE_CO2STANDBY								  		0xA6			//  * * CO₂待命	CO₂处于待命状态		低
    , G_WARN_PRIORITY_LOW//		G_WARN_T_CODE_CO2STOP							  		0xA7			//  * * *CO₂通讯停止	CO₂模块和主机通讯出现问题		低


};
CGlbWarn::CGlbWarn()
{
    int iModifyFlg = 0;
    int warn_corusecate;    //报警暂停标志,G_WARN_CORUSECATE_OFF不暂停，G_WARN_CORUSECATE_ON暂停
    int warn_pause_time ;//报警暂停时间G_WARN_PAUSE_TIME_1，1分钟；G_WARN_PAUSE_TIME_2，2分钟。
    int warn_para_lock; //参数报警是否栓锁
    int warn_record_flg; //报警记录开关标志G_WARN_RECORD_ON，记录；G_WARN_RECORD_OFF，不记录。
    int warn_voice_flg;
    int warn_voice_volume;
    QFile file(G_WARN_CFG_DOC);

    //读取配置文档的内容
    if (file.open(QIODevice::ReadOnly))
    {
        QDataStream inout(&file);
        int magic;
        inout >> magic;
        if(magic == 0x12345678)
         {
            inout>>warn_corusecate>>
                warn_pause_time
             >>warn_para_lock
            >>warn_record_flg
            >>warn_voice_flg
              >>warn_voice_volume;
          }
         file.close();

        //设置报警配置
        if((warn_corusecate !=G_WARN_CORUSECATE_ON )&&((warn_corusecate !=G_WARN_CORUSECATE_OFF )))
        {
            //默认配置
            warn_corusecate = G_WARN_CORUSECATE_OFF;
            iModifyFlg = true;
        }
       m_stWarnCfg.m_warn_corusecate = warn_corusecate;

        if((warn_pause_time !=G_WARN_PAUSE_TIME_2 )
                &&(warn_pause_time !=G_WARN_PAUSE_TIME_1 ))

        {
            //默认配置
            warn_pause_time = G_WARN_PAUSE_TIME_1;
             iModifyFlg = true;
        }
        m_stWarnCfg.m_warn_pause_time = warn_pause_time;

        if((warn_para_lock !=G_WARN_PARA_LOCK_ON )
            &&(warn_para_lock !=G_WARN_PARA_LOCK_OFF))
        {
            //默认配置
            warn_para_lock = G_WARN_PARA_LOCK_ON;
             iModifyFlg = true;
        }

       m_stWarnCfg.m_warn_para_lock = warn_para_lock;

        if((warn_record_flg !=G_WARN_RECORD_OFF )
                &&(warn_record_flg !=G_WARN_RECORD_ON ))
        {
            //默认配置
            warn_record_flg = G_WARN_RECORD_ON;
             iModifyFlg = true;
        }
        m_stWarnCfg.m_warn_record_flg = warn_record_flg;

        if((warn_voice_flg !=G_WARN_VOICE_OFF )
            &&(warn_voice_flg !=G_WARN_VOICE_ON ))
        {
            //默认配置
            warn_voice_flg = G_WARN_VOICE_ON;
             iModifyFlg = true;
        }
        m_stWarnCfg.m_warn_voice_flg = warn_voice_flg;

        if((warn_voice_volume >G_WARN_VOICE_VOL_3 )||(warn_voice_volume <G_WARN_VOICE_VOL_0))
        {
            //默认配置
            warn_voice_volume = G_WARN_VOICE_VOL_2;
             iModifyFlg = true;
        }
        m_stWarnCfg.m_warn_voice_volume = warn_voice_volume;
        if( iModifyFlg == true)
        {
            file.open(QIODevice::WriteOnly);
            QDataStream out(&file);
            magic = 0x12345678;
            out << magic;
            out <<warn_corusecate
                <<warn_pause_time
               <<warn_para_lock
               <<warn_record_flg
               <<warn_voice_flg
               <<warn_voice_volume;
            file.flush();
            file.close();
        }

     }
    else //文档不存在，写入默认配置
    {
        f_setDefaultCfg();
    }


}
CGlbWarn::~CGlbWarn()
{

}
void CGlbWarn::f_getConfig(stWarnCfg *cfg)
{
    cfg->m_warn_corusecate = m_stWarnCfg.m_warn_corusecate;
    cfg->m_warn_para_lock = m_stWarnCfg.m_warn_para_lock;
    cfg->m_warn_pause_time = m_stWarnCfg.m_warn_pause_time;
    cfg->m_warn_record_flg = m_stWarnCfg.m_warn_record_flg;
    cfg->m_warn_voice_flg = m_stWarnCfg.m_warn_voice_flg;
    cfg->m_warn_voice_volume = m_stWarnCfg.m_warn_voice_volume;
}

void CGlbWarn::f_setConfig(stWarnCfg stCfg)
{
    int warn_corusecate;    //报警暂停标志,G_WARN_CORUSECATE_OFF不暂停，G_WARN_CORUSECATE_ON暂停
    int warn_pause_time ;//报警暂停时间G_WARN_PAUSE_TIME_1，1分钟；G_WARN_PAUSE_TIME_2，2分钟。
    int warn_para_lock; //参数报警是否栓锁
    int warn_record_flg; //报警记录开关标志G_WARN_RECORD_ON，记录；G_WARN_RECORD_OFF，不记录。
    int warn_voice_flg;
    int warn_voice_volume;

    warn_corusecate = stCfg.m_warn_corusecate;
    warn_pause_time = stCfg.m_warn_pause_time;
    warn_para_lock = stCfg.m_warn_para_lock;
    warn_record_flg = stCfg.m_warn_record_flg;
    warn_voice_flg = stCfg.m_warn_voice_flg;
    warn_voice_volume = stCfg.m_warn_voice_volume;

    //设置报警配置
    if(warn_corusecate >G_WARN_CORUSECATE_ON )
    {

        warn_corusecate = m_stWarnCfg.m_warn_corusecate;
    }
    else{
        m_stWarnCfg.m_warn_corusecate = warn_corusecate;
    }
    if(warn_pause_time >G_WARN_PAUSE_TIME_2 )
    {
        //默认配置
        warn_pause_time = m_stWarnCfg.m_warn_pause_time;
    }
    else{
        m_stWarnCfg.m_warn_pause_time = warn_pause_time;
    }
    if(warn_para_lock >G_WARN_PARA_LOCK_ON )
    {
        //默认配置
        warn_para_lock = m_stWarnCfg.m_warn_para_lock;
    }
    else{
        m_stWarnCfg.m_warn_para_lock = warn_para_lock;
    }
    if(warn_record_flg >G_WARN_RECORD_OFF )
    {
        //默认配置
        warn_record_flg = m_stWarnCfg.m_warn_record_flg;
    }
    else{
        m_stWarnCfg.m_warn_record_flg = warn_record_flg;
    }
    if(warn_voice_flg >G_WARN_VOICE_OFF )
    {
        //默认配置
        warn_voice_flg = m_stWarnCfg.m_warn_voice_flg;
    }
    else{
        m_stWarnCfg.m_warn_voice_flg = warn_voice_flg;
    }
    if(warn_voice_volume >G_WARN_VOICE_VOL_3 )
    {
        //默认配置
        warn_voice_volume = m_stWarnCfg.m_warn_voice_volume;
    }
    else{
        m_stWarnCfg.m_warn_voice_volume = warn_voice_volume;
    }

     //写入配置文档的内容
      QFile file(G_WARN_CFG_DOC);
     if (file.open(QIODevice::WriteOnly))
     {
         QDataStream out(&file);
         int magic = 0x12345678;
         out << magic;
         out <<warn_corusecate
             <<warn_pause_time
            <<warn_para_lock
            <<warn_record_flg
            <<warn_voice_flg
            <<warn_voice_volume;

         file.close();
         }

}
void CGlbWarn::f_setDefaultCfg()
{
    int warn_corusecate;    //报警暂停标志,G_WARN_CORUSECATE_OFF不暂停，G_WARN_CORUSECATE_ON暂停
    int warn_pause_time ;//报警暂停时间G_WARN_PAUSE_TIME_1，1分钟；G_WARN_PAUSE_TIME_2，2分钟。
    int warn_para_lock; //参数报警是否栓锁
    int warn_record_flg; //报警记录开关标志G_WARN_RECORD_ON，记录；G_WARN_RECORD_OFF，不记录。
    int warn_voice_flg;
    int warn_voice_volume;

    m_stWarnCfg.m_warn_corusecate =  warn_corusecate = G_WARN_CORUSECATE_OFF;
    m_stWarnCfg.m_warn_pause_time =  warn_pause_time = G_WARN_PAUSE_TIME_1;
     m_stWarnCfg.m_warn_para_lock = warn_para_lock = G_WARN_PARA_LOCK_OFF;
    m_stWarnCfg.m_warn_record_flg =  warn_record_flg = G_WARN_RECORD_ON;
     m_stWarnCfg.m_warn_voice_flg = warn_voice_flg = G_WARN_VOICE_ON;
     m_stWarnCfg.m_warn_voice_volume = warn_voice_volume = G_WARN_VOICE_VOL_2;
     //写入配置文档的内容
      QFile file(G_WARN_CFG_DOC);
     if (file.open(QIODevice::WriteOnly))
     {
         QDataStream out(&file);
         int magic = 0x12345678;
         out<< magic;

             out<<warn_corusecate
                 <<warn_pause_time
                <<warn_para_lock
                <<warn_record_flg
                <<warn_voice_flg
                <<warn_voice_volume;
         file.close();
     }
}
void CGlbWarn::f_addWarn(int iWarnCode,QString strWarnTxt, int cWarnPriority)
{
    if(cWarnPriority == G_WARN_PRIORITY_HIGH)
    {
        if((iWarnCode >=0)&&(iWarnCode <0x7f)) //判断错误代码与优先级是否匹配
        {
            m_warn_code_high.append(iWarnCode);
            m_warn_txt_high.append(strWarnTxt);
        }
    }
    else if(cWarnPriority == G_WARN_PRIORITY_MID)
    {
        if((iWarnCode >=0)&&(iWarnCode <0x7f)) //判断错误代码与优先级是否匹配
        {
            m_warn_code_mid.append(iWarnCode);
            m_warn_txt_mid.append(strWarnTxt);
        }
    }
    else if(cWarnPriority == G_WARN_PRIORITY_LOW)
    {
        if((iWarnCode >=0x80)&&(iWarnCode <0xff)) //判断错误代码与优先级是否匹配
        {
            m_warn_code_low.append(iWarnCode);
            m_warn_txt_low.append(strWarnTxt);
        }
    }
}

void CGlbWarn::f_readWarn(int *iWarnCode, QString *strWarnTxt, int *iWarnPri)
{
    if( !m_warn_code_high.isEmpty())
    {
        *iWarnCode = m_warn_code_high.first();
        *strWarnTxt = m_warn_txt_high.first();
        *iWarnPri =G_WARN_PRIORITY_HIGH;
        if(m_stWarnCfg.m_warn_para_lock == G_WARN_PARA_LOCK_OFF) //参数报警非栓锁，删掉此报警
        {
                m_warn_code_high.removeFirst();
                m_warn_txt_high.removeFirst();

        }
        else
        {
                m_warn_code_high.append(*iWarnCode);
                m_warn_txt_high.append(*strWarnTxt);
        }
    }
    else if ( !m_warn_code_mid.isEmpty())
    {
        *iWarnPri =G_WARN_PRIORITY_MID;
    }
    else if ( !m_warn_txt_low.isEmpty())
    {
        *iWarnPri =G_WARN_PRIORITY_LOW;
    }
}
/*
//iMethod 解除报警的方式：
G_WARN_PARA_DEL_KEY 0    //按键解除参数报警
 G_WARN_PARA_DEL_AUTO 1 //自动解除参数报警
 //iWarnCode 报警代码

*/
 void CGlbWarn::f_delWarn(int iMethod,int iWarnCode)
 {
     int iIndx = 0;
     if(iMethod  == G_WARN_PARA_DEL_KEY)
     {

     }
     else if(iMethod == G_WARN_PARA_DEL_AUTO)
     {
         //处于参数栓锁状态，只能手动解除
            if(m_stWarnCfg.m_warn_para_lock == G_WARN_PARA_LOCK_ON)
            {
                return;
            }
     }
     //解除报警信息
     if(iWarnCode == G_WARN_PRIORITY_HIGH)
     {
         iIndx = m_warn_code_high.indexOf(iWarnCode);
         if(iIndx>=0)
         {

         }
     }
     else if(iWarnCode == G_WARN_PRIORITY_MID)
      {
        iIndx =m_warn_code_mid.indexOf(iWarnCode);
        if(iIndx>=0)
        {

        }
     }
     else if(iWarnCode == G_WARN_PRIORITY_LOW)
    {
        iIndx =m_warn_code_low.indexOf(iWarnCode);
         if(iIndx>=0)
         {

         }
     }
 }
