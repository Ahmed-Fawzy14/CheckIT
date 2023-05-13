#include "mainwindow.h"
#include "Mainia.h"
#include "qforeach.h"
#include "ui_mainwindow.h"
#include<iostream>
#include<unordered_set>
#include <utility>
#include <QString>
#include "qtextedit.h"
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QRegularExpression>



float jaccardSimilarity(const unordered_set<string>& set1, const unordered_set<string>& set2) {
    unordered_set<string> intersection;
    unordered_set<string> unionSet;

    // Calculate intersection
    for (const auto& ngram : set1) {
        if (set2.count(ngram) > 0) {
            intersection.insert(ngram);
        }
    }

    // Calculate union
    unionSet = set1;
    for (const auto& ngram : set2) {
        unionSet.insert(ngram);
    }

    float jaccard = static_cast<float>(intersection.size()) / unionSet.size();

    return jaccard;
}

//Get N-Grams for Jaccard
vector<string> generateNGrams(const string& str, int n) {
    vector<string> ngrams;
    for (int i = 0; i <= str.length() - n; i++) {
        ngrams.push_back(str.substr(i, n));
    }
    return ngrams;
}

//Calculates the percentage of similarity in the corpus vs the main using Jaccard Similarity
void similarityPercent(string main, string c1, string c2, string c3) {

    vector<string> suspiciousNGrams = generateNGrams(main, 5);
    std::unordered_set<std::string> suspiciousSet(suspiciousNGrams.begin(), suspiciousNGrams.end());

    vector<string> referenceNGrams = generateNGrams(c1, 5);
    std::unordered_set<std::string> referenceSet(referenceNGrams.begin(), referenceNGrams.end());
    //a lot of plagarism trace it
    float similarity = jaccardSimilarity(suspiciousSet, referenceSet);
    if (similarity >= 0.5) {
        cout << "Similarity of: " << similarity * 100 << "% suggests plagarism";
    }
    else if (similarity <= 0.5 && similarity >= 25) {
        cout << "Similarity of: " << similarity * 100 << "% is slightly high";
    }
    else
        cout << "No Plagarism";

}

list<pair<string, string>> printPoly(unordered_map<string, string> foundPolySentences, unordered_map<string, string> foundPoly4Phrases, unordered_map<string, string> foundPoly3Phrases, unordered_map<string, string> foundPoly2Phrases, int document) {
    list<pair<string, string>> foundList;
    string color{};


   /* if (document == 1) {
        color = "yellow";
    }
    else if (document == 2) {
        color = "blue";
    }
    else
        color = "white";*/

    color = "yellow";
    string color1 = "blue";

    if (foundPoly4Phrases.empty()) {
        std::cout << "foundPoly4Phrases is empty!" << std::endl;
    }

    if (foundPoly3Phrases.empty()) {
        std::cout << "foundPoly3Phrases is empty!" << std::endl;
    }

    if (foundPoly2Phrases.empty()) {
        std::cout << "foundPoly2Phrases is empty!" << std::endl;
    }

    if (foundPolySentences.empty()) {
        std::cout << "foundPolySentences is empty!" << std::endl;
    }

    //make first one color and second string
    for (auto it = foundPoly4Phrases.begin(); it != foundPoly4Phrases.end(); it++) {
        foundList.push_back({ color , foundPoly4Phrases[it->first]});
    }

    for (auto it = foundPoly3Phrases.begin(); it != foundPoly3Phrases.end(); it++) {
        foundList.push_back({ color1 , foundPoly3Phrases[it->first]});
    }

    for (auto it = foundPoly2Phrases.begin(); it != foundPoly2Phrases.end(); it++) {
        foundList.push_back({ color1 , foundPoly2Phrases[it->first] });

    }

    for (auto it = foundPolySentences.begin(); it != foundPolySentences.end(); it++) {
        foundList.push_back({ color , foundPolySentences[it->first]});

    }


    return foundList;
}

void printFinger() {


}

QList<QPair<QString, QString>> convertList(const std::list<std::pair<std::string, std::string>>& inputList) {
    QList<QPair<QString, QString>> outputList;
    for (const auto& pair : inputList) {
        QPair<QString, QString> qPair(QString::fromStdString(pair.first), QString::fromStdString(pair.second));
        outputList.append(qPair);
    }
    return outputList;
}

/*string displayText(const QList<QPair<QString, QString>>& results, QTextEdit* textEdit, const MainWindow &w)
{

}*/




/*vector<wstring> RabinKarp::stem(string str, int i, vector<wstring> w) {
    if (i >= str.size()) {
        return w;
    }
    string strShort{};
    strShort = calcBound(str, i, 1);
    strShort = oneremoveSpaces(strShort, 1);
    stemming::english_stem<> StemEnglish;
    wstring_convert<codecvt_utf8_utf16<wchar_t>> converter; // create a converter object

    wstring wide_str = converter.from_bytes(strShort); // convert narrow string to wide string
    StemEnglish(wide_str);

    w.push_back(wide_str);

    return stem(str, i, w);
}

wstring RabinKarp::stem(string str) {
    string strShort{};
    strShort = oneCalcBound(str, 1);
    strShort = oneremoveSpaces(str, 1);
    stemming::english_stem<> StemEnglish;
    wstring_convert<codecvt_utf8_utf16<wchar_t>> converter; // create a converter object

    wstring wide_str = converter.from_bytes(strShort); // convert narrow string to wide string
    StemEnglish(wide_str);

  //  stem(str, i);

    return wide_str;
}*/


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void highlightText(QList<QPair<QString, QString>> Qfound, QTextEdit *textEdit) {
    QTextCursor cursor = textEdit->textCursor();
    QTextCharFormat highlightFormat;
    QString foundText;

    for (const auto &pair : Qfound) {
        highlightFormat.setBackground(QColor(pair.first));
        foundText = pair.second;
        int pos = textEdit->toPlainText().indexOf(foundText);
        while (pos != -1) {
            cursor.setPosition(pos);
            cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, foundText.length());
            cursor.setCharFormat(highlightFormat);
            pos = textEdit->toPlainText().indexOf(foundText, pos + 1);
        }
    }

}


/*int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Create a QWidget to hold the textEdit
    QWidget window;

    // Create a QVBoxLayout to hold the textEdit
    QVBoxLayout *layout = new QVBoxLayout(&window);

    // Create a QTextEdit to hold the text
    QTextEdit *textEdit = new QTextEdit();
    textEdit->setPlainText("This is some example text to highlight.");
    textEdit->setReadOnly(true);

    // Add the textEdit to the layout
    layout->addWidget(textEdit);

    // Define the substrings to highlight and their colors in a list
    QList<QPair<QString, QString>> highlightList;
    highlightList.append(QPair<QString, QString>("example text", "yellow"));
    highlightList.append(QPair<QString, QString>("text to", "yellow"));
    highlightList.append(QPair<QString, QString>("text to highlight", "yellow"));

    // Highlight the substrings in the text
    highlight(highlightList, textEdit);

    window.show();
    return app.exec();
}
*/


QString convertToQString(const std::string& str) {
    return QString::fromStdString(str);
}

void MainWindow::on_pushButton_3_clicked()
{
//ui->textEdit->setText("AHmed");
    //objects
    Phrases p;
    Sentences s;
    RabinKarp rk;
    MainWindow w;


// create a new QTextEdit widget

    QList<QPair<QString, QString>> Qfound;


    //maps
    //maps
    //POLY
    unordered_map<string, string> foundPoly4PhrasesC1 = {};
    unordered_map<string, string> foundPoly3PhrasesC1 = {};
    unordered_map<string, string> foundPoly2PhrasesC1 = {};

    unordered_map<string, string> foundPoly4PhrasesC2 = {};
    unordered_map<string, string> foundPoly3PhrasesC2 = {};
    unordered_map<string, string> foundPoly2PhrasesC2 = {};

    unordered_map<string, string> foundPoly4PhrasesC3 = {};
    unordered_map<string, string> foundPoly3PhrasesC3 = {};
    unordered_map<string, string> foundPoly2PhrasesC3 = {};



    unordered_map<string, string> foundPolySentencesC1 = {};
    unordered_map<string, string> foundPolySentencesC2 = {};
    unordered_map<string, string> foundPolySentencesC3 = {};

    //FINGERPRINT
    unordered_map<string, string> foundFinger4Phrases = {};
    unordered_map<string, string> foundFinger3Phrases = {};
    unordered_map<string, string> foundFinger2Phrases = {};
    unordered_map<string, string> foundFingerSentences = {};

    list<pair<string, string>> foundListPoly;
    list<pair<string, string>> foundListPolyTemp;

    list<pair<string, string>> foundList;


    QString name2= "C:/Users/Fawzy/OneDrive - YAT learning Solutions/Documents/SPD_FINAL/Corp1.txt";

    QString name1= "C:/Users/Fawzy/OneDrive - YAT learning Solutions/Documents/SPD_FINAL/Sus.txt";

    QString name3= "C:/Users/Fawzy/OneDrive - YAT learning Solutions/Documents/SPD_FINAL/Corp2.txt";

    QString name4= "C:/Users/Fawzy/OneDrive - YAT learning Solutions/Documents/SPD_FINAL/Corp3.txt";
    //files
    string c1 = rk.readFile(name2);

    string c2 = rk.readFile(name3);

    string c3 = rk.readFile(name4);

    string main = rk.readFile(name1);

   // vector<wstring> w;


  //  w = rk.stem(main, 0, w);
//I have sent the main now I need to make w work with everyhitng else


    //found = rabinKarp(main, c1, c2, c3);
    foundPoly4PhrasesC1 = p.rabinKarpPolyPhrases(main, c1, 4);
    foundPoly3PhrasesC1 = p.rabinKarpPolyPhrases(main, c1, 3);
    foundPoly2PhrasesC1 = p.rabinKarpPolyPhrases(main, c1, 2);

    foundPoly4PhrasesC2 = p.rabinKarpPolyPhrases(main, c2, 4);
    foundPoly3PhrasesC2 = p.rabinKarpPolyPhrases(main, c2, 3);
    foundPoly2PhrasesC2 = p.rabinKarpPolyPhrases(main, c2, 2);

    foundPoly4PhrasesC3 = p.rabinKarpPolyPhrases(main, c3, 4);
    foundPoly3PhrasesC3 = p.rabinKarpPolyPhrases(main, c3, 3);
    foundPoly2PhrasesC3 = p.rabinKarpPolyPhrases(main, c3, 2);
    //still need to fix in sentences
    foundPolySentencesC1 = s.rabinKarpPolySentences(main, c1);
    foundPolySentencesC2 = s.rabinKarpPolySentences(main, c2);
    foundPolySentencesC3 = s.rabinKarpPolySentences(main, c3);


    //firgure out how to send doucment
    //C1
    foundListPoly = printPoly(foundPolySentencesC1, foundPoly4PhrasesC1, foundPoly3PhrasesC1, foundPoly2PhrasesC1, 0);

    //C2
    foundListPolyTemp = printPoly(foundPolySentencesC2, foundPoly4PhrasesC2, foundPoly3PhrasesC2, foundPoly2PhrasesC2, 0);

    foundListPoly.insert(foundListPoly.end(), foundListPolyTemp.begin(), foundListPolyTemp.end());

    //C3
    foundListPolyTemp = printPoly(foundPolySentencesC3, foundPoly4PhrasesC3, foundPoly3PhrasesC3, foundPoly2PhrasesC3, 0);


    foundListPoly.insert(foundListPoly.end(), foundListPolyTemp.begin(), foundListPolyTemp.end());


    Qfound = convertList(foundListPoly);

    //look at setTextColor
    QString myQString = convertToQString(main);

    ui->textEdit->setText(myQString);

//WORKING BABY
  /* for (auto& Qfound : Qfound)
    {
        QString line = Qfound.second + "\n";
        ui->textEdit->append(line);
    }*/
////////////////////////////////////////////////
//highlight is carshing the program
    highlightText(Qfound, ui->textEdit);


//couts the raw found to the text edit
  /*  for (const auto& p : Qfound) {
        QString x =  "(" + p.first + ", " + p.second + ")" + '\n';
        ui->textEdit->append(x);

    }*/


    //fingerprint
    //figure out how to writw this normally
    /* for (auto it = found.begin(); it != found.end(); it++) {
         cout << it->first << '\t' << it->second << endl;

     }*/




      similarityPercent(main, c1, c2, c3);

      //Now I have:
      //Jaccard sim working but i need to understand it
      //RK is working with the things need to find a nice way to priont
      // loop i think is solved
      //multiple docs either need to be the same size or I would need to use seperate fucntion or smth else idk yet    ui->textEdit->setText("Ahmed");
}

