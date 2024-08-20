QT       += core gui \

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
qt/addressbookpage.cpp \
qt/bitcoinunits.cpp \
qt/intro.cpp \
qt/paymentserver.cpp \
qt/receiverequestdialog.cpp \
qt/transactiondescdialog.cpp \
qt/walletmodel.cpp \
qt/addresstablemodel.cpp \
qt/clientmodel.cpp \
qt/main.cpp \
qt/peertablemodel.cpp \
qt/recentrequeststablemodel.cpp \
qt/transactionfilterproxy.cpp \
qt/walletmodeltransaction.cpp \
qt/askpassphrasedialog.cpp \
qt/coincontroldialog.cpp \
qt/modaloverlay.cpp \
qt/peertablesortproxy.cpp \
qt/rpcconsole.cpp \
qt/transactionoverviewwidget.cpp \
qt/walletview.cpp \
qt/bantablemodel.cpp \
qt/coincontroltreewidget.cpp \
qt/networkstyle.cpp \
qt/platqt/formstyle.cpp \
qt/sendcoinsdialog.cpp \
qt/transactionrecord.cpp \
qt/winshutdownmonitor.cpp \
qt/bitcoinaddressvalidator.cpp \
qt/createwalletdialog.cpp \
qt/notificator.cpp \
qt/psbtoperationsdialog.cpp \
qt/sendcoinsentry.cpp \
qt/transactiontablemodel.cpp \
qt/bitcoinamountfield.cpp \
qt/csvmodelwriter.cpp \
qt/openuridialog.cpp \
qt/qrimagewidget.cpp \
qt/signverifymessagedialog.cpp \
qt/transactionview.cpp \
qt/bitcoin.cpp \
qt/editaddressdialog.cpp \
qt/optionsdialog.cpp \
qt/qvalidatedlineedit.cpp \
qt/splashscreen.cpp \
qt/utilitydialog.cpp \
qt/bitcoing.ui \.cpp \
qt/g.ui \util.cpp \
qt/optionsmodel.cpp \
qt/qvaluecombobox.cpp \
qt/trafficgraphwidget.cpp \
qt/walletcontroller.cpp \
qt/bitcoinstrings.cpp \
qt/initexecutor.cpp \
qt/overviewpage.cpp \
qt/receivecoinsdialog.cpp \
qt/transactiondesc.cpp \
qt/walletframe.cpp \


HEADERS += \
qt/addressbookpage.h \
qt/clientmodel.h \
qt/intro.h \
qt/optionsmodel.h \
qt/qvaluecombobox.h \
qt/splashscreen.h \
qt/utilitydialog.h \
qt/addresstablemodel.h \
qt/coincontroldialog.h \
qt/macdockiconhandler.h \
qt/overviewpage.h \
qt/receivecoinsdialog.h \
qt/trafficgraphwidget.h \
qt/walletcontroller.h \
qt/askpassphrasedialog.h \
qt/coincontroltreewidget.h \
qt/macnotificationhandler.h \
qt/paymentserver.h \
qt/receiverequestdialog.h \
qt/transactiondescdialog.h \
qt/walletframe.h \ qt/bantablemodel.h \
qt/createwalletdialog.h \
qt/macos_appnap.h \
qt/peertablemodel.h \
qt/recentrequeststablemodel.h \  qt/transactiondesc.h \
qt/walletmodel.h \ qt/bitcoinaddressvalidator.h \
qt/csvmodelwriter.h \
qt/modaloverlay.h \
qt/peertablesortproxy.h \
qt/rpcconsole.h \
qt/transactionfilterproxy.h \
qt/walletmodeltransaction.h \
qt/bitcoinamountfield.h \
qt/editaddressdialog.h \
qt/networkstyle.h \
qt/platqt/formstyle.h \
qt/sendcoinsdialog.h \
qt/transactionoverviewwidget.h \
qt/walletview.h \ bitcoing.ui \.h \
qt/g.ui \constants.h \           notificator.h \
qt/psbtoperationsdialog.h \  sendcoinsentry.h \
qt/transactionrecord.h \
qt/winshutdownmonitor.h \
qt/bitcoin.h \
qt/g.ui \util.h \
qt/openuridialog.h \
qt/qrimagewidget.h \
qt/sendcoinsrecipient.h \
qt/transactiontablemodel.h \
qt/bitcoinunits.h \
qt/initexecutor.h \
qt/optionsdialog.h \
qt/qvalidatedlineedit.h \
qt/signverifymessagedialog.h \
qt/transactionview.h \


FORMS += \
qt/forms/addressbookpage.ui \
qt/forms/createwalletdialog.ui \
qt/forms/helpmessagedialog.ui \
qt/forms/openuridialog.ui \
qt/forms/psbtoperationsdialog.ui \
qt/forms/sendcoinsdialog.ui \
qt/forms/transactiondescdialog.ui \
qt/forms/askpassphrasedialog.ui \
qt/forms/debugwindow.ui \
qt/forms/intro.ui \
qt/forms/optionsdialog.ui \
qt/forms/receivecoinsdialog.ui \
qt/forms/sendcoinsentry.ui \
qt/forms/coincontroldialog.ui \
qt/forms/editaddressdialog.ui \
qt/forms/modaloverlay.ui \
qt/forms/overviewpage.ui \
qt/forms/receiverequestdialog.ui \
qt/forms/signverifymessagedialog.ui \

INCLUDEPATH+= qt/
INCLUDEPATH+= ../



    
