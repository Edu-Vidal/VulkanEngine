#pragma once

// Indices of Queue Families
struct QueueFamilyIndices
{
	int graphicsFamily = -1;

	// Check if queue families are valid
	bool isValid()
	{
		return graphicsFamily >= 0;
	}

};