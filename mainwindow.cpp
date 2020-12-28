#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Book Management System"); //Sets main window title

    //Connections
    connect(ui->submit_btn, &QPushButton::clicked, this, &MainWindow::submit_btn_clicked);
    connect(ui->clear_btn, &QPushButton::clicked, this, &MainWindow::clear_lineEdit);
    connect(ui->filter_btn, &QPushButton::clicked, this, &MainWindow::update_by_filter);
    connect(ui->title_filter_rb, &QPushButton::toggled, this, &MainWindow::toggle_title_cb);
    connect(ui->isbn_filter_rb, &QPushButton::toggled, this, &MainWindow::toggle_isbn_cb);

    //Init Functions
    loadMap();
    print_map();
    loadComboBox();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::write_to_file()
{
    QFile book_io("books.txt");
    if(!book_io.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate))
    {
        qDebug()<< "Error Loading Data File\n";
    }
    QTextStream out(&book_io);
    //out << "The magic number is: " << 49 << "\n";
        // library_books(QString a, uint64_t i, QString g, QString t, QString e, int y, int num_c = 1, bool availability = true, QString li="N/A", QString sg ="N/A"):Book (a, i, g, t, e, y)
    for (auto it : bMap)
    {
        out << it.get_title() << Qt::endl;
        out << it.get_author()<< Qt::endl;
        out << it.get_genre()<< Qt::endl;
        out << it.get_subgenre() << Qt::endl;
        out << it.get_publisher() << Qt::endl;
        out << it.get_edition_year() << Qt::endl;
        out << it.get_isbn()<< Qt::endl;
        out << it.get_number_of_copies() << Qt::endl;
        out << it.get_library_id() << Qt::endl;
        out << it.get_availability() << Qt::endl;
    }
    book_io.close();
    qDebug() << "FILE WRITTEN" << Qt::endl;
}


void MainWindow::loadMap()
{
    QFile books_file("books.txt");
    if(!books_file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Invalid file";
    }

    QTextStream in(&books_file);
    while(!in.atEnd()){
        int num;
        bool av = true;
        QString tit = in.readLine();
        QString auth = in.readLine();
        QString gen = in.readLine();
        QString subgen = in.readLine();
        QString pub = in.readLine();
        int year = in.readLine().toInt();
        int is = in.readLine().toULong();
        num = in.readLine().toInt();
        QString libid = in.readLine();
        int avail = in.readLine().toInt();
        //qDebug() << "DEBUG AVAIL: " <<avail;
        if (avail == 0){
               av = false;
        }
        // library_books(QString a, uint64_t i, QString g, QString t, QString e, int y, int num_c = 1, bool availability = true, QString li="N/A", QString sg ="N/A"):Book (a, i, g, t, e, y)
        library_books new_book(auth,is, gen, tit, pub, year, num, av, libid, subgen);
        bMap.insert(is, new_book);
    }
    books_file.close();
}

void MainWindow::submit_btn_clicked()
{
    loadMap();
    // library_books(QString a, uint64_t i, QString g, QString t, QString e, int y, int num_c = 1, bool availability = true, QString li="N/A", QString sg ="N/A"):Book (a, i, g, t, e, y)
    library_books new_book(ui->author_input->text(),
                           ui->isbn_input->text().toULong(),
                           ui->genre_input->text(),
                           ui->title_input->text(),
                           ui->publisher_input->text(),
                           ui->edition_year_date->text().toInt(),
                           ui->qty_sb->text().toInt(),
                           true,
                           ui->library_id_input->text(),
                           ui->subgenre_input->text());

    bMap.insert(ui->isbn_input->text().toULong(), new_book);
    write_to_file();
    loadComboBox();
    print_map();
    clear_lineEdit();
}

void MainWindow::update_by_filter()
{
    for  (auto i : bMap) {
        if(ui->title_filter_rb->isChecked())
        {
            if(i.get_title() ==  ui->title_filter_cb->currentText()){
                ui->title_r_identifier->setText(i.get_title());
                ui->author_r_identifier->setText(i.get_author());
                ui->isbn_r_identifier->setText(QString::number(i.get_isbn()));
                ui->genre_r_identifier->setText(i.get_genre());
                break;
            }
        }
        else if(ui->isbn_filter_rb->isChecked()){
            if(QString::number(i.get_isbn()) ==  ui->isbn_filter_cb->currentText()){
                ui->title_r_identifier->setText(i.get_title());
                ui->author_r_identifier->setText(i.get_author());
                ui->isbn_r_identifier->setText(QString::number(i.get_isbn()));
                ui->genre_r_identifier->setText(i.get_genre());
                break;
            }
        }
    }
}

void MainWindow::toggle_title_cb()
{
    if(ui->title_filter_rb->isChecked())
    {
        ui->title_filter_cb->setEnabled(true);
    }
    else{
        ui->title_filter_cb->setEnabled(false);
    }
}

void MainWindow::toggle_isbn_cb()
{
    if(ui->isbn_filter_rb->isChecked())
    {
        ui->isbn_filter_cb->setEnabled(true);
    }
    else{
        ui->isbn_filter_cb->setEnabled(false);
    }
}


void MainWindow::clear_lineEdit()
{
    ui->title_input->clear();
    ui->author_input->clear();
    ui->isbn_input->clear();
    ui->genre_input->clear();
}


void MainWindow::loadComboBox()
{
    ui->title_filter_cb->clear();
    ui->isbn_filter_cb->clear();
    for(auto i : bMap)
    {
        ui->title_filter_cb->addItem(i.get_title());
        ui->isbn_filter_cb->addItem(QString::number(i.get_isbn()));
        //ui->id_filter_cb->addItem(QString::number(i.get_id()));
    }
}

void MainWindow::print_map()
{
    for(auto it : bMap){
        qDebug() << "Title" << it.get_title();
        qDebug() << "Author:" << it.get_author();
        qDebug() << "ISBN:" << it.get_isbn();
        qDebug() << "Genre" << it.get_genre();
        //qDebug() << "Book ID" << it.get_id();
        qDebug() << "Number of Copies" << it.get_number_of_copies();
        qDebug() << "Availability" << it.get_availability();
        //qDebug() << Qt::endl;
    }
}
