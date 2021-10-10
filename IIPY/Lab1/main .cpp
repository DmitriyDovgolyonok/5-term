#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
    string id, vendor, device, str, nameV, nameD;
    ifstream stream, data;
    stream.open("/proc/bus/pci/devices");
    if (!stream.is_open()) {
        cout << "\nError opening the file";
        exit(-1);
    }
    data.open("pci.ids");
    if (!stream.is_open()) {
        cout << "\nError opening the file";
        exit(-1);
    }
    cout << "VendorID" << setw(33)<< "DeviceID" << endl << endl;
    while(!stream.eof())
    {
        stream >> id;
        stream >> id;
        vendor = id;
        vendor.erase(4, 4);
        device = id.erase(0, 4);
        getline(stream, id);
        while(!data.eof())
        {
            getline(data, str);
            if (str.find(vendor) == 0) {
                nameV = str;
                cout << nameV;
                break;
            }
        }
        while(!data.eof())
        {
            getline(data, str);
            if (str.find(device) != string::npos ) {
                nameD = str;
                cout << "       " << nameD << endl;
                break;
            }
            if (str == "C ff  Unassigned class") {
                cout << "         " << device << endl;
                break;
            }
        }
        data.seekg(0, std::ios_base::beg);
    }
    stream.close();
    data.close();
    return 0;
}
