#include "BookForm.h"
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

BookForm::BookForm(QWidget *parent) : QWidget(parent)
{
    //Elements
    QLabel *label_author = new QLabel("Autor", this);
    QComboBox *author = new QComboBox(this);

    QLabel *label_title = new QLabel("Titel", this);
    QLineEdit *title = new QLineEdit(this);

    QLabel *label_publisher = new QLabel("Verlag", this);
    QComboBox *publisher = new QComboBox(this);

    QLabel *label_year = new QLabel("Erscheinungsjahr", this);
    QSpinBox *year = new QSpinBox(this);

    QLabel *label_quote = new QLabel("Zitat:", this);
    QTextEdit *quote = new QTextEdit(this);

    QPushButton *ok = new QPushButton("Ok", this);
    QPushButton *cancel = new QPushButton("Cancel", this);

    //Layout
    QHBoxLayout *hlayout_author = new QHBoxLayout;
       hlayout_author->addWidget(label_author);
       hlayout_author->addWidget(author);

    QHBoxLayout *hlayout_title = new QHBoxLayout;
       hlayout_title->addWidget(label_title);
       hlayout_title->addWidget(title);

    QHBoxLayout *hlayout_publisher = new QHBoxLayout;
       hlayout_publisher->addWidget(label_publisher);
       hlayout_publisher->addWidget(publisher);

    QHBoxLayout *hlayout_year = new QHBoxLayout;
       hlayout_year->addWidget(label_year);
       hlayout_year->addWidget(year);

    QHBoxLayout *hlayout_quote = new QHBoxLayout;
          hlayout_quote->addWidget(label_quote);
          hlayout_quote->addWidget(quote);

    QHBoxLayout *hlayout_button = new QHBoxLayout;
       hlayout_button->addSpacing(100);
       hlayout_button->addWidget(ok);
       hlayout_button->addWidget(cancel);

    QVBoxLayout *vlayout = new QVBoxLayout;
       vlayout->addLayout(hlayout_author);
       vlayout->addLayout(hlayout_title);
       vlayout->addLayout(hlayout_publisher);
       vlayout->addLayout(hlayout_year);
       vlayout->addLayout(hlayout_quote);
       vlayout->addLayout(hlayout_button);
       setLayout(vlayout);

     //Properties
       author->setEditable(true);
       author->addItem("<Neuer Autor>");

       publisher->setEditable(true);
       publisher->addItem("<Neuer Verlag>");

       year->setMinimum(2000);
       year->setMaximum(2099);

       QObject::connect(ok, SIGNAL(clicked()), this, SLOT(close()));
       QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(close()));
}
