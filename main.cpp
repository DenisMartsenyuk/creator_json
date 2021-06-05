#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Point {
public:

    Point(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    string getString() {
        return "[" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + "]";
    }

private:
    double x, y, z;
};

string getHeader(int progress) {
    return "{\n\t\"type\": \"PROGRESS\",\n\t\"progress\": " + to_string(progress) + ",\n\t\"points\": [";
}

string  getEnd() {
    return "\n\t]\n}";
}

int main() {
    ifstream fin("/Users/mega_user/Desktop/SCANNER ПО/creator_json/Elka.obj");
    vector<Point> points;
    while (!fin.eof()) {
        char type;
        double x, y, z;
        fin >> type >> x >> y >> z;
        points.push_back(Point(x, y, z));
    }


    cout << floor(points.size() / 360);

    for (int i = 0, j = 0; i < 360; ++i) {
        ofstream fout("/Users/mega_user/Desktop/SCANNER ПО/creator_json/jsons/" + to_string(i) + ".json");
        string header = getHeader(round(i * 1.0 / 360 * 100));
        string points_str = "";
        for (; j < (i + 1) * floor(points.size() / 360); ++j) {
            if (j + 1 >= (i + 1) * floor(points.size() / 360)) {
                points_str = points_str + "\n\t\t" + points[j].getString();
            } else {
                points_str = points_str + "\n\t\t" + points[j].getString() + ",";
            }
        }

        fout << header << points_str << getEnd();
        fout.close();
    }
    return 0;
}
