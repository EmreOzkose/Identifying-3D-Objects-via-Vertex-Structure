// Opengl Libraries
#include <Angel_commons/Angel.h>
#include <glui.h>

#include <vector>

// Own Libraries
#include "model.h"
#include "read.h"

// Standart Libraries
using namespace std;


int main(){
	Model *model = new Model;
	model = read_weights(model);			// Read trained weights. Model is given for hyper-parameters


	const int num_of_vertices = model->num_of_vertex;
	std::vector<float> test_object[num_of_vertices] = { std::vector<float> {0.1f, 0.2f, 0.3f, 1.0f} };

	const int out_dim = model->output_dim;
	float outputs [out_dim];

	float *probs = model->forward(test_object);
	
	for (int i = 0; i < out_dim; i++)
		cout << probs[i] << endl;
	

	cout << "Done !" << endl;
	while (1);
}
