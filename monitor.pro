HEADERS += \
    qextserialbase.h \
    posix_qextserialport.h \
    mainform.h \    
    rsc_record/menu_record.h \
    rsc_record/dlg_record_qushitu.h \
    rsc_record/dlg_record_qushibiao.h \
    rsc_record/dlg_record_nibp.h \
    rsc_record/dlg_record_boxing.h \
    rsc_record/dlg_record_alarm.h \
    rsc_pmng/menu_patient_mng.h \
    rsc_pmng/form_patient_info.h \
    rsc_pmng/form_patient_drug.h \
    rsc_pmng/form_patient_diding.h \
    rsc_alarm/menu_alarm_limit.h \
    rsc_serve/menu_serve.h \
    rsc_set/menu_set.h \
    rsc_set/dlg_set_color.h \
    rsc_set/dlg_set_alarm.h \
    rsc_set/dlg_set_record.h \
    rsc_set/dlg_set_screen_layout.h \
    rsc_set/dlg_set_time.h \
    rsc_set/dlg_set_others.h \
    rsc_set/dlg_set_ecg.h \
    rsc_set/dlg_set_spo2.h \
    rsc_set/dlg_set_nibp.h \
    rsc_set/dlg_set_spire.h \
    rsc_set/dlg_set_temp.h \
    rsc_set/dlg_set_ibp.h \
    rsc_set/dlg_set_co2.h \
    rsc_set/dlg_set_eeg.h \
    rsc_set/dlg_set_mashen.h \
    rsc_alarm/dlg_alm_ecg.h \
    rsc_alarm/dlg_alm_spo2.h \
    rsc_alarm/dlg_alm_nibp.h \
    rsc_alarm/dlg_alm_spire.h \
    rsc_alarm/dlg_alm_temp.h \
    rsc_alarm/dlg_alm_mashen.h \
    rsc_alarm/dlg_alm_ibp.h \
    rsc_alarm/dlg_alm_co2.h \
    rsc_serve/dlg_serv_man_config.h \
    rsc_serve/dlg_serv_man_para.h \
    rsc_serve/dlg_serv_tiwentantou.h \
    rsc_serve/dlg_serv_usr.h \
    rsc_serve/dlg_serv_xindianjiaozhun.h \
    rsc_warning/glb_warning.h \
    rsc_warning/glb_warning1.txt \
    main.h \
    rsc_plot/plotter.h \
    rsc_plot/waveplot.h \
    rsc_modu/module.h \
    rsc_modu/modu_ecg.h \
    rsc_modu/layout.h \
    rsc_modu/modu_eeg.h \
    rsc_modu/color.h \
    rsc_modu/modu_thread.h \
    rsc_modu/modu_anaes.h \
    rsc_modu/modu_co2.h \
    rsc_modu/modu_ibp.h \
    rsc_modu/modu_netthread.h \
    rsc_modu/modu_net.h \
    rsc_modu/modu_database.h \
    rsc_modu/filter_one.h \
    rsc_modu/modu_system.h \
    rsc_modu/modu_play.h \
    rsc_modu/modu_gpio.h \
    rsc_modu/gpio_lib.h \
    rsc_modu/gpio.h \
    keyboard.h \
    keyboard_context.h

SOURCES += \
    qextserialbase.cpp \
    posix_qextserialport.cpp \
    mainform.cpp \
    main.cpp \
    rsc_record/menu_record.cpp \
    rsc_record/dlg_record_qushitu.cpp \
    rsc_record/dlg_record_qushibiao.cpp \
    rsc_record/dlg_record_nibp.cpp \
    rsc_record/dlg_record_boxing.cpp \
    rsc_record/dlg_record_alarm.cpp \
    rsc_pmng/menu_patient_mng.cpp \
    rsc_pmng/form_patient_info.cpp \
    rsc_pmng/form_patient_drug.cpp \
    rsc_pmng/form_patient_diding.cpp \
    rsc_alarm/menu_alarm_limit.cpp \
    rsc_serve/menu_serve.cpp \
    rsc_set/menu_set.cpp \
    rsc_set/dlg_set_alarm.cpp \
    rsc_set/dlg_set_record.cpp \
    rsc_set/dlg_set_screen_layout.cpp \
    rsc_set/dlg_set_others.cpp \
    rsc_set/dlg_set_ecg.cpp \
    rsc_set/dlg_set_spo2.cpp \
    rsc_set/dlg_set_nibp.cpp \
    rsc_set/dlg_set_spire.cpp \
    rsc_set/dlg_set_temp.cpp \
    rsc_set/dlg_set_ibp.cpp \
    rsc_set/dlg_set_co2.cpp \
    rsc_set/dlg_set_eeg.cpp \
    rsc_set/dlg_set_mashen.cpp \
    rsc_alarm/dlg_alm_ecg.cpp \
    rsc_alarm/dlg_alm_spo2.cpp \
    rsc_alarm/dlg_alm_nibp.cpp \
    rsc_alarm/dlg_alm_spire.cpp \
    rsc_alarm/dlg_alm_temp.cpp \
    rsc_alarm/dlg_alm_mashen.cpp \
    rsc_alarm/dlg_alm_ibp.cpp \
    rsc_alarm/dlg_alm_co2.cpp \
    rsc_serve/dlg_serv_man_config.cpp \
    rsc_serve/dlg_serv_man_para_config.cpp \
    rsc_serve/dlg_serv_tiwentantou.cpp \
    rsc_serve/dlg_serv_xindianjiaozhun.cpp \
    rsc_warning/glb_warning.cpp \
    rsc_plot/plotter.cpp \
    rsc_modu/module.cpp \
    rsc_modu/layout.cpp \
    rsc_modu/modu_anaes.cpp \
    rsc_modu/modu_co2.cpp \
    rsc_modu/modu_ibp.cpp \
    rsc_modu/modu_database.cpp \
    key.cpp \
    rsc_modu/modu_thread.cpp \
    rsc_modu/filter_one.cpp \
    rsc_plot/waveplot.cpp \
    rsc_set/dlg_set_color.cpp \
    rsc_set/dlg_set_time.cpp \
    rsc_serve/dlg_serv_usr.cpp \
    rsc_modu/modu_netthread.cpp \
    rsc_modu/modu_system.cpp \
    rsc_modu/modu_net.cpp \
    rsc_modu/modu_ecg.cpp \
    rsc_modu/modu_eeg.cpp \
    rsc_modu/modu_play.cpp \
    rsc_modu/gpio_lib.cpp \
    rsc_modu/gpio.cpp \
    rsc_modu/modu_gpio.cpp \
    keyboard.cpp \
    keyboard_context.cpp

RESOURCES += \
    maiform.qrc \


FORMS += \ 
    ui_dlg/untitled.ui \
    ui_dlg/test.ui \
    ui_dlg/set_wifi_dlg.ui \
    ui_dlg/set_time_dlg.ui \
    ui_dlg/set_spo2_dlg.ui \
    ui_dlg/set_qitashezhi_dlg.ui \
    ui_dlg/set_pingmubuju_dlg.ui \
    ui_dlg/set_nibp_dlg.ui \
    ui_dlg/set_mashen_dlg.ui \
    ui_dlg/set_jilushezhi_dlg.ui \
    ui_dlg/set_ibp_dlg.ui \
    ui_dlg/set_color_dlg.ui \
    ui_dlg/set_co2_dlg.ui \
    ui_dlg/set_alm_dlg.ui \
    ui_dlg/serv_xindianjiaozhun_dlg.ui \
    ui_dlg/serv_usr_dlg.ui \
    ui_dlg/serv_usr_config_para_dlg.ui \
    ui_dlg/serv_tiwentantou_dlg.ui \
    ui_dlg/serv_man_config_para_dlg.ui \
    ui_dlg/serv_man_config_dlg.ui \
    ui_dlg/pmng_yaowujisuan.ui \
    ui_dlg/pmng_patient_info.ui \
    ui_dlg/pmng_patient_drug.ui \
    ui_dlg/pmng_delete_p_info.ui \
    ui_dlg/pmng_bingrenxinxi.ui \
    ui_dlg/mainform.ui \
    ui_dlg/keyboard_E.ui \
    ui_dlg/keyboard_e.ui \
    ui_dlg/his_qushitu_dlg.ui \
    ui_dlg/his_qushibiao_dlg.ui \
    ui_dlg/his_nibp_huigu_dlg.ui \
    ui_dlg/his_boxing_dlg.ui \
    ui_dlg/his_alarm_dlg.ui \
    ui_dlg/alm_nibp_dlg.ui \
    ui_dlg/alm_mashen_dlg.ui \
    ui_dlg/alm_ibp_dlg.ui \
    ui_dlg/alm_ecg_dlg.ui \
    ui_dlg/set_spire_dlg.ui \
    ui_dlg/set_temp_dlg.ui \
    ui_dlg/set_eeg_dlg.ui \
    ui_dlg/set_ecg_dlg.ui \
    ui_dlg/alm_co2_dlg.ui \
    ui_dlg/alm_spire_dlg.ui \
    ui_dlg/alm_temp_dlg.ui \
    ui_dlg/alm_spo2_dlg.ui \
    ui_dlg/serv_usr_config_dlg.ui \
    keyboard.ui

OTHER_FILES += \
    rsc_warning/warning2.txt
QT += network
QT  += sql

#LIBS +=-L/usr/lib -lasound
LIBS += -L/usr/share/arm-alsa/lib -lasound

