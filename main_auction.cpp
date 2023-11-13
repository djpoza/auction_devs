#include <cadmium/core/logger/csv.hpp>
#include <cadmium/core/simulation/root_coordinator.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <limits>
#include "auction.hpp"
#include "input_data.hpp"

using namespace cadmium::example::auction;

int main() { //int argc, char *argv[]) {    
    // We create the model and forward it to the root coordinator
    // NOTE THAT WE NEED A POINTER TO THE MODEL!
       
    std::vector<std::vector<int>> matrix = read_matrix();
    std::vector<int> ID_b;
    for (int i=1; i<=matrix[0].size(); i++){
    ID_b.push_back(i);
    }
    std::string name_f_b = "Buyers_prices.txt";
    info_agents l_buyers = read_agents(name_f_b);
    std::vector<double> RPr = l_buyers._Pr;
    std::vector<double> InitialPPr = l_buyers._InitialPr;
    std::vector<int> ID_s;
    for (int j=1; j<=matrix.size(); j++){
    ID_s.push_back(j);
    }
    std::string name_f_s = "Sellers_prices.txt";
    info_agents l_sellers = read_agents(name_f_s);
    std::vector<double> PCost = l_sellers._Pr; 
    std::vector<double> InitialAPr = l_sellers._InitialPr;

    auto model = std::make_shared<auction>("auction",  ID_b,RPr, 5.0, InitialPPr ,ID_s ,PCost , 5.0, InitialAPr , matrix, 4.0); 

   // auto model = std::make_shared<auction>("auction",{"1","2","3"}, {40.0,30.0,20.0}, 5.0, {20.0,15.0,10.0}, {"1","2","3"}, {20.0,30.0,50.0}, 10.0, {30.0,50.0,70.0}, 4.0); 

    // Next, we create the coordinator and the logger
    // We can add a logger to the root coordinator
    // In this example, we use a CSV logger that uses ; to separate columns.
    // Simulation results will be stored in the log_gpt.csv file.
    auto rootCoordinator = cadmium::RootCoordinator(model);
    auto logger = std::make_shared<cadmium::CSVLogger>("log_auction.csv", ";");
    rootCoordinator.setLogger(logger);

    // To start the simulation we 1) start, 2) simulate 3) stop.
    rootCoordinator.start();
    // in simulate method, we can select a maximum simulation time (in this case, infinity)
    rootCoordinator.simulate((double) 120);
    //rootCoordinator.simulate(std::numeric_limits<double>::infinity());
    rootCoordinator.stop();

    return 0;
}
