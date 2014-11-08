#include <QCoreApplication>
#include <iostream>
#include "utl/USmartPtr.h"
#include "utl/UStack.h"

using namespace utl;
using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    SetMinLogLevel(LOG_ERROR);
    Stack<int> * b1 = new Stack<int>();
    b1->Push(5);
    Stack<int> * b2 = new Stack<int>(10);
    b2 = b1;
    for(int i = 0; i < 10; i++) {
        b2->Push(i);
    }
    while(!b2->Empty()) {
        LOG(INFO)<<"Value = "<<b2->Pop();
    }
    return a.exec();
}
