#include "library_data.h"

QString library_books::get_author()
{
    return author;
}

uint64_t library_books::get_isbn()
{
    return isbn;
}

QString library_books::get_genre()
{
    return genre;
}

QString library_books::get_title()
{
    return title;
}

QString library_books::get_subgenre()
{
    return sub_genre;
}

QString library_books::get_library_id()
{
    return library_id;
}

QString library_books::get_publisher()
{
    return publisher;
}

bool library_books::get_availability()
{
    return availability;
}

int library_books::get_number_of_copies()
{
    return number_of_copies;
}

int library_books::get_edition_year()
{
  return edition_year;
}
