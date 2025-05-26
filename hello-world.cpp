#include <string>
#include "common.h"
#include "docbuilder.h"

// Specify the path to the Document Builder work directory and the result path (where the generated file will be saved)
#define WORK_DIRECTORY L"builder/opt/onlyoffice/documentbuilder"

using namespace NSDoctRenderer;

int main(int argc, char *argv[])
{
    // Init DocBuilder
    CDocBuilder::Initialize(WORK_DIRECTORY);
    CDocBuilder oBuilder;
    oBuilder.SetProperty("--work-directory", WORK_DIRECTORY);

    oBuilder.CreateFile(OFFICESTUDIO_FILE_DOCUMENT_DOCX);

    CContext oContext = oBuilder.GetContext();
    CContextScope oScope = oContext.CreateScope();

    CValue oGlobal = oContext.GetGlobal();

    CValue oApi = oGlobal["Api"];
    CValue oDocument = oApi.Call("GetDocument");
    CValue oParagraph = oApi.Call("CreateParagraph");
    oParagraph.Call("SetSpacingAfter", 1000, false);
    oParagraph.Call("AddText", "Hello, world!");
    CValue oContent = oContext.CreateArray(1);
    oContent[0] = oParagraph;
    oDocument.Call("InsertContent", oContent);

    // Save and close
    std::wstring sDstPath = L"result.docx";
    oBuilder.SaveFile(OFFICESTUDIO_FILE_DOCUMENT_DOCX, sDstPath.c_str());
    oBuilder.CloseFile();

    CDocBuilder::Dispose();

    return 0;
}
