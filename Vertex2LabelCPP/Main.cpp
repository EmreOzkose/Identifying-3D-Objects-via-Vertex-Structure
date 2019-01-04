// Opengl Libraries
#include <Angel_commons/Angel.h>
#include <glui.h>

#include <vector>

// Own Libraries
#include "definitions.h"
#include "model.h"
#include "read.h"

// Standart Libraries
using namespace std;


int main(){
	Model *model = new Model;
	model = read_weights(model);			// Read trained weights. Model is given for hyper-parameters
	
	// Create a test object
	const int num_of_vertices = num_of_vertex;
	vector<vector<float>> test_object[num_of_vertices];

	// Initialize the test object
	for (int i = 0; i < num_of_vertices; i++)
		test_object->push_back(vector<float> {-0.1f, 0.2f, 0.3f, 1.0f});

	vector<float> probs = model->forward(test_object);
	
	const int out_dim = output_dim;
	for (int i = 0; i < out_dim; i++)
		cout << probs.at(i) << endl;
	

	cout << "Done !" << endl;
	while (1);
}
