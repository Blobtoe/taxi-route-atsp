#include "../include/adjacency_matrix.hpp"
#include "../include/timer.hpp"
#include "../include/brute_force.hpp"
#include "../include/held_karp.hpp"
#include "../include/json.hpp"

#include <time.h>
#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include <curl/curl.h>

#define earthRadiusKm 6371.0 // radius of the earth in km

namespace nh = nlohmann;

// converts decimal degrees to radians
double deg2rad(double deg) {
  return (deg * M_PI / 180);
}

// thanks stackoverflow (https://stackoverflow.com/questions/10198985/calculating-the-distance-between-2-latitudes-and-longitudes-that-are-saved-in-a)
double distanceEarth(std::pair<double, double> point1, std::pair<double, double> point2) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(point1.first);
  lon1r = deg2rad(point1.second);
  lat2r = deg2rad(point2.first);
  lon2r = deg2rad(point2.second);
  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v)) * 1000;
}

// thanks stackoverflow (https://stackoverflow.com/questions/36702888/download-an-image-from-an-url-using-curl-in-c)
size_t callbackfunction(void *ptr, size_t size, size_t nmemb, void* userdata)
{
    FILE* stream = (FILE*)userdata;
    if (!stream)
    {
        printf("!!! No stream\n");
        return 0;
    }

    size_t written = fwrite((FILE*)ptr, size, nmemb, stream);
    return written;
}

bool download_jpeg(const char* url)
{
    FILE* fp = fopen("solution.jpg", "wb");
    if (!fp)
    {
        printf("!!! Failed to create file on the disk\n");
        return false;
    }

    CURL* curlCtx = curl_easy_init();
    curl_easy_setopt(curlCtx, CURLOPT_URL, url);
    curl_easy_setopt(curlCtx, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(curlCtx, CURLOPT_WRITEFUNCTION, callbackfunction);
    curl_easy_setopt(curlCtx, CURLOPT_FOLLOWLOCATION, 1);

    CURLcode rc = curl_easy_perform(curlCtx);
    if (rc)
    {
        printf("!!! Failed to download: %s\n", url);
        return false;
    }

    int res_code = 0;
    curl_easy_getinfo(curlCtx, CURLINFO_RESPONSE_CODE, &res_code);
    if (!((res_code == 200 || res_code == 201) && rc != CURLE_ABORTED_BY_CALLBACK))
    {
        printf("!!! Response code: %d\n", res_code);
        return false;
    }

    curl_easy_cleanup(curlCtx);

    fclose(fp);

    return true;
}

class Route {
    public:
        std::pair<double, double> start;
        std::pair<double, double> end;
        double length;
        //double revenue;
        Route() {};
        Route(std::pair<double, double> start, std::pair<double, double> end/*, double revenue*/) : start(start), end(end)/*, revenue(revenue)*/ {
            length = distanceEarth(start, end);
        }
};

void from_json(const nh::json& j, Route& val) {
    j.at("start").get_to(val.start);
    j.at("end").get_to(val.end);
    //j.at("revenue").get_to(val.revenue);
    val.length = distanceEarth(val.start, val.end);
}

void to_json(nh::json& j, const Route& val) {
    j["start"] = val.start;
    j["end"] = val.end;
    j["length"] = val.length;
    //j["revenue"] = val.revenue;
}

class Solution {
    public:
        std::pair<double, double> start_point;
        std::vector<Route> routes;
        double total_length = 0;
        //double total_revenue = 0;
        //int route_count;
        Solution() {};
        Solution(std::vector<Route> routes/*, int route_count*/, std::pair<double, double> start_point) : routes(routes)/*, route_count(route_count)*/, start_point(start_point) {
            // if (route_count == 0)
            //     return;
            total_length = distanceEarth(start_point, routes.at(0).start) + routes.at(0).length;
            //total_revenue = routes.at(0).revenue;
            //for (int i = 1; i < route_count; i++)
            for (int i = 1; i < routes.size(); i++)
            {
                total_length += distanceEarth(routes.at(i-1).end, routes.at(i).start) + routes.at(i).length;
                //total_revenue += routes.at(i).revenue;
            }
        }
};

void to_json(nh::json& j, const Solution& val) {
    j["routes"] = val.routes;
    j["total_length"] = val.total_length;
    //j["total_revenue"] = val.total_revenue;
    //j["route_count"] = val.route_count;
    j["start_point"] = val.start_point;
}

void from_json(const nh::json& j, Solution& val) {
    j.at("routes").get_to(val.routes);
    j.at("start_point").get_to(val.start_point);
    val.total_length = distanceEarth(val.start_point, val.routes.at(0).start) + val.routes.at(0).length;
        for (int i = 1; i < val.routes.size(); i++)
            val.total_length += distanceEarth(val.routes.at(i-1).end, val.routes.at(i).start) + val.routes.at(i).length;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    // read problem from file
    std::ifstream fin(argv[1]);
    std::string line;
    std::string raw_json;
    if (!fin.is_open()){
        std::cout << "Failed to open problem file\n";
        return 1;
    }
    while (getline(fin, line))
        raw_json.append(line);
    fin.close();

    std::cout << "Opened file\n";

    // parse problem
    Solution initial_solution = nh::json::parse(raw_json);

    std::cout << "Parsed problem\n";

    int matrix_size = initial_solution.routes.size() + 1;
    std::vector<std::vector<int>> t_matrix(matrix_size);
    std::vector<int> row(matrix_size);

    // create start_point distances row
    row.at(0) = 0;
    for (int i = 0; i < matrix_size-1; i++)
        row.at(i) = round(distanceEarth(initial_solution.start_point, initial_solution.routes.at(i).start));
    t_matrix.at(0) = row;

    // create rest of distance matrix
    for (int i = 0; i < matrix_size-1; i++) {
        row.at(0) = 0;
        for (int j = 0; j < matrix_size-1; j++)
        {
            if (i == j)
                row.at(j+1) = 0;
            else
                row.at(j+1) = round(distanceEarth(initial_solution.routes.at(i).end, initial_solution.routes.at(j).start));
        }
        t_matrix.at(i+1) = row;
    }

    std::cout << "Generated matrix\n";

    // convert to adjacency matrix
    Adjacency_Matrix matrix = Adjacency_Matrix(t_matrix);
    std::cout << "Converted to Adjacency Matrix\n";
    std::cout << matrix.to_string();

    std::cout << "Running Algorithm\n";

    // run algorithm
    auto brutef{tsp::held_karp(matrix)};
    auto t{Timer<Path>([&brutef]() { return brutef.run(); })};
    double time{t.run()};

    std::cout << "Done\n";

    // shouw output
    std::cout << "Solution:\n";
    std::cout << t.get_output().to_string();
    std::cout << "  Time [ms] >> " << time << std::endl;

    std::vector<Route> routes(t.get_output().path_.size()-2);
    for (int i = 0; i < t.get_output().path_.size()-2; i++)
        routes.at(i) = initial_solution.routes.at(t.get_output().path_.at(i+1)-1);
    Solution solution = Solution(routes, initial_solution.start_point);
    
    // create url of image
    std::cout << "Creating url\n";
    std::string url = "https://www.mapquestapi.com/staticmap/v5/map?key=hKH3hnlVzLGhlckZqYYjahwOIuU82z1U&locations=" +  std::to_string(initial_solution.start_point.first) + "," +  std::to_string(initial_solution.start_point.second) + "|marker-blue-s||";
    for (int i = 0; i < initial_solution.routes.size(); i++)
        url +=  std::to_string(initial_solution.routes.at(i).start.first) + "," +  std::to_string(initial_solution.routes.at(i).start.second) + "|marker-green-" + std::to_string(i+1) + "||" +  std::to_string(initial_solution.routes.at(i).end.first) + "," +  std::to_string(initial_solution.routes.at(i).end.second) + "|marker-red-" + std::to_string(i+1) + "||";
    for (int i = 0; i < initial_solution.routes.size(); i++)
        url += "&shape=" +  std::to_string(initial_solution.routes.at(i).start.first) + "," + std::to_string(initial_solution.routes.at(i).start.second) + "|" + std::to_string(initial_solution.routes.at(i).end.first) + "," + std::to_string(initial_solution.routes.at(i).end.second);
    url += "&shape=border:ff0000|" + std::to_string(solution.start_point.first) + "," + std::to_string(solution.start_point.second) + "|" + std::to_string(solution.routes.at(0).start.first) + "," + std::to_string(solution.routes.at(0).start.second);
    for (int i = 1; i < solution.routes.size(); i++)
        url += "&shape=border:ff0000|" + std::to_string(solution.routes.at(i-1).end.first) + "," + std::to_string(solution.routes.at(i-1).end.second) + "|" + std::to_string(solution.routes.at(i).start.first) + "," + std::to_string(solution.routes.at(i).start.second);
    url += "&size=1000,1000@2x";

    // download the image
    std::cout << "Downloading image\n";
    download_jpeg(url.c_str());

    // write solution to file
    std::cout << "Saving solution to file\n";
    nh::json j = solution;
    std::ofstream fout;
    fout.open("solution.json");
    fout << j;
    fout.close();

    return 0;
}