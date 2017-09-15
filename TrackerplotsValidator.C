#include <TGClient.h>
#include <TCanvas.h>
#include <TF1.h>
#include "TSystem.h"
#include "TGFrame.h"
#include "TGFileBrowser.h"

class Validator {
public:
    Validator(const TGWindow *p, UInt_t w, UInt_t h);
    string FilenameFromDialog();
    void LoadReferenceButton();
    void LoadCurrentButton();
    void createComparisonPlots();
    int HistogramIntersectionSimilarity(TH1 *A, TH1 *B);
    void initResources();

//    Only for testing purposes
//    string reference_file_str = "/home/fil/projects/TrackerplotsValidator/pre3.root";
//    string current_file_str = "/home/fil/projects/TrackerplotsValidator/pre5.root";

    string reference_file_str = "";
    string current_file_str = "";

private:
    TGMainFrame *fMain;

    TGTextEntry *reference_text;
    TGTextEntry *current_text;

    TGTextButton *reference_loadbtn;
    TGTextButton *current_loadbtn;
    TGTextButton *plot_btn;

    TGFileDialog *loadDialog;

    vector<string> plot_dirs;
    vector<string> plot_names;

    TObject *find_plot_in_file(TDirectory *baseDir, string file_name_to_find);
};

TObject *Validator::find_plot_in_file(TDirectory *baseDir, string file_name_to_find) {
    TIter next(baseDir->GetListOfKeys());
    TKey *key;

    while ((key = (TKey *)next())) {
        TClass *cl = gROOT->GetClass(key->GetClassName());

        if (cl->InheritsFrom("TH1")) {
            TH1 *h = (TH1 *)key->ReadObj();
            string fname = h->GetName();
            if (!fname.compare(file_name_to_find)) {
                return h;
            }
        }
    }
    cout << "[WARNING] Resource " << file_name_to_find << " not found." << endl;
    return 0;
}

Validator::Validator(const TGWindow *p, UInt_t w, UInt_t h) {
    fMain = new TGMainFrame(p, w, h);

    TGHorizontalFrame *reference_group = new TGHorizontalFrame(fMain);
    TGHorizontalFrame *current_group = new TGHorizontalFrame(fMain);

    reference_text = new TGTextEntry(reference_group);
    reference_loadbtn = new TGTextButton(reference_group, "Load Reference");
    reference_group->AddFrame(reference_loadbtn, new TGLayoutHints(kLHintsLeft, 2, 2, 2, 2));
    reference_group->AddFrame(reference_text, new TGLayoutHints(kLHintsExpandX, 2, 2, 2, 2));

    current_text = new TGTextEntry(current_group);
    current_loadbtn = new TGTextButton(current_group, "Load Current  ");
    current_group->AddFrame(current_loadbtn, new TGLayoutHints(kLHintsLeft, 2, 2, 2, 2));
    current_group->AddFrame(current_text, new TGLayoutHints(kLHintsExpandX, 2, 2, 2, 2));

    TGHorizontalFrame *plot_group = new TGHorizontalFrame(fMain);
    plot_btn = new TGTextButton(plot_group, "Create Comparison Plot");
    plot_group->AddFrame(plot_btn, new TGLayoutHints(kLHintsCenterX, 2, 2, 2, 2));

    fMain->AddFrame(reference_group, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX, 2, 2, 2, 2));
    fMain->AddFrame(current_group, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX, 2, 2, 2, 2));
    fMain->AddFrame(plot_group, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX, 2, 2, 2, 2));

    reference_loadbtn->Connect("Clicked()", "Validator", this, "LoadReferenceButton()");
    current_loadbtn->Connect("Clicked()", "Validator", this, "LoadCurrentButton()");
    plot_btn->Connect("Clicked()", "Validator", this, "createComparisonPlots()");

    reference_text->SetEnabled(false);
    current_text->SetEnabled(false);

    fMain->SetWindowName("Trackerplots Validator");
    fMain->MapSubwindows();
    fMain->MoveResize(100, 100, 520, 85);
    fMain->MapWindow();

    initResources();
}

void Validator::LoadReferenceButton() {
    string path = FilenameFromDialog();
    reference_text->SetText(path.c_str());
    reference_file_str = path;
}

void Validator::LoadCurrentButton() {
    string path = FilenameFromDialog();
    current_text->SetText(path.c_str());
    current_file_str = path;
}

string Validator::FilenameFromDialog() {
    TGFileInfo file_info_;
    const char *filetypes[] = {"ROOT files", "*.root", 0, 0};
    file_info_.fFileTypes = filetypes;
    loadDialog = new TGFileDialog(gClient->GetDefaultRoot(), fMain, kFDOpen, &file_info_);

    return file_info_.fFilename ? file_info_.fFilename : "";
}

// returns similarity in percent, based on intersection:
//
// sim(A,B) = Integral(A intersect B) / Integral(A)
//   in the discrete case this gives us
// sim(A,B) = Sum min(A(i),B(i)) / Sum A(i)
//
int Validator::HistogramIntersectionSimilarity(TH1 *A, TH1 *B) {
    int nbins = A->GetXaxis()->GetNbins();

    int a, b;
    int sum = 0;
    int total_a = 0;
    for (int i = 0; i < nbins; ++i) {
        a = A->GetBinContent(i);
        b = B->GetBinContent(i);
        sum += min(a, b);
        total_a += a;
    }
    return round(100 * (float)sum / (float)total_a);
}

void TrackerplotsValidator() {
    new Validator(gClient->GetRoot(), 200, 200);
}

void Validator::initResources() {
    // define the resources to be searched
    plot_dirs.push_back("DQMData/Run 1/SiStrip/Run summary/MechanicalView/TOB");        // #1
    plot_dirs.push_back("DQMData/Run 1/SiStrip/Run summary/MechanicalView/TIB");        // #2
    plot_dirs.push_back("DQMData/Run 1/SiStrip/Run summary/MechanicalView/TEC/MINUS");  // #3
    plot_dirs.push_back("DQMData/Run 1/SiStrip/Run summary/MechanicalView/TID/PLUS");   // #4
    plot_dirs.push_back("DQMData/Run 1/PixelPhase1/Run summary/Phase1_MechanicalView"); // #5
    plot_dirs.push_back("DQMData/Run 1/PixelPhase1/Run summary/Phase1_MechanicalView"); // #6


    plot_names.push_back("Summary_ClusterStoNCorr_OnTrack__TOB");        // #1
    plot_names.push_back("Summary_ClusterStoNCorr_OnTrack__TIB");        // #2
    plot_names.push_back("Summary_ClusterStoNCorr_OnTrack__TEC__MINUS"); // #3
    plot_names.push_back("Summary_ClusterStoNCorr_OnTrack__TID__PLUS");  // #4
    plot_names.push_back("charge_PXBarrel");                             // #5
    plot_names.push_back("charge_PXForward");                            // #6
}

void Validator::createComparisonPlots() {
    if(reference_file_str.empty() || current_file_str.empty()) {
        cout << "Select a reference and current file for comparison!" << endl;
        return;
    }

    TFile *reference_file = TFile::Open(reference_file_str.c_str());
    TFile *current_file = TFile::Open(current_file_str.c_str());

    if(reference_file && current_file)
        cout << "[ OK ] Opening Files" << endl;
    else
        cout << "[FAIL] Opening Files" << endl;

    vector<pair<TObject *, TObject *>> plots;

    // do all the plot lookups in the files
    TDirectory *ref_dir = nullptr;
    TDirectory *cur_dir = nullptr;

    for (int idx = 0; idx < plot_names.size(); ++idx) {
        ref_dir = (TDirectory *)reference_file->Get(plot_dirs[idx].c_str());
        cur_dir = (TDirectory *)current_file->Get(plot_dirs[idx].c_str());

        plots.push_back(make_pair(find_plot_in_file(ref_dir, plot_names[idx]),
                                  find_plot_in_file(cur_dir, plot_names[idx])));
    }

    // plot all the things that we've gathered
    TCanvas *resultCanvas = new TCanvas("Result Canvas", "", 900, 800);
    resultCanvas->Divide(2, 3);

    cout << endl << "=========================== Summary =========================== " << endl;

    cout << "Reference: \t" << reference_file_str << endl;
    cout << "Current: \t" << current_file_str << endl << endl;;

    int i = 1;
    for (auto &e : plots) {
        resultCanvas->cd(i++);

        if (e.first && e.second) {
            ((TH1 *)e.first)->SetLineColor(kBlue);
            ((TH1 *)e.second)->SetMarkerStyle(2);

            e.first->Draw("same");
            e.second->Draw("same p");

            auto legend = new TLegend(0.65,0.8,0.85,0.9);
            legend->AddEntry(e.first,"Reference", "l");
            legend->AddEntry(e.second, "Current");
            legend->Draw();

            int similarity = HistogramIntersectionSimilarity((TH1 *)e.first, (TH1 *)e.second);

            if (similarity >= 95) cout << "[ OK ] ";
            else cout << "[FAIL] ";

            cout << similarity << "% intersection similarity \t" << e.first->GetTitle() << endl;
        } else {
            cout << "[SKIP] Either Reference or Current plot is empty!" << endl;
        }
    }
    cout << endl << "=============================================================== " << endl;
}
