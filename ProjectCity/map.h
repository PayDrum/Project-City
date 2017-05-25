#pragma once

#include <string>

class map {

private:
	static const unsigned int gridX = 10;
	static const unsigned int gridY = 10;

	

	const std::string TerraformLayerName = "Terraform Layer";
	const std::string UndergroundLayerName = "Underground piping Layer";
	const std::string PopulationLayerName = "Population distribution Layer";
	const std::string RoadLayerName = "Road Layer";
	const std::string SubwayLayerName = "Subway Layer";

public:

	int getGridX() { return gridX; }
	int getGridY() {return gridY;}

	map();
	~map();



};