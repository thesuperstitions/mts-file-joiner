//---------------------------------------------------------------------------
#ifndef MTS_FileJoinerH
#define MTS_FileJoinerH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
  TOpenDialog *OpenDialog1;
  TPanel *Panel1;
  TPanel *Panel2;
  TBitBtn *BitBtn1;
  TMemo *Memo1;
  TOpenDialog *OpenDialog2;
  TBitBtn *BitBtn2;
  void __fastcall BitBtn1Click(TObject *Sender);
  void __fastcall BitBtn2Click(TObject *Sender);
  void __fastcall Panel2Resize(TObject *Sender);

private:	// User declarations
  void GetNextFileName(char* filename);
  void LogMessage(char* Msg);

public:		// User declarations
  __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
