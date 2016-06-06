#include"BPNN_Recommendation.h"
#include "stdafx.h"
#include "network.h"
#include "BPLearning.h"
#include "sigmodfunction.h"
#include "activefunction.h"

#define NodeNum 260    //vector dimension
#define CASENUM 5551    //cases num
#define ACCURACY 0.03 
#define TIME 3000

extern double accuracy = 0.9;
extern double accuracyCurr = 0.0;

////extern function////
vector<WeightArticle> getTopN_Y(vector<WeightArticle>& base, ALGO mode, int top_n)
{
	vector<WeightArticle> v(top_n + 1); // + 1 to reserve a temp position
	
	int n = base.size();
	for (int i = 0; i < n; i++)
	{
		v[top_n] = base[i];
		int j = top_n;
		while ((j > 0) && (v[j-1].weight[mode] <= v[j].weight[mode]))
		{
			swap(v[j-1], v[j]);
			j--;
		}
	}

	v.erase(v.end()-1); // erase the temp
	return v;
}

/**********************************************************************
*
***********************************************************************/
BPNN_Recommendation::BPNN_Recommendation(vector<User*>& userList, vector<Article*>& articleList)
{
	m_userList = userList;
	m_articleList = articleList;
	m_answer.clear();

	m_accuracy = 0.0; 
	m_x = m_y = 0.0;
}

void BPNN_Recommendation::loadAnswerFromFile(string fileName)
{
	ifstream inAn(fileName);
	if(inAn.fail())
	{
		cout << "ERROR: fail open answer.txt..." << endl;
		return;
	}

	vector<int> an;
	char p[10] = {0};
	int startPos = 0;

	while(!inAn.eof())
	{
		an.clear();
		string str("");
		getline(inAn, str);
		while(1 && str != "")
		{
			int pos = str.find('\t', startPos + 1);
			if(pos != string::npos)
			{
				if(startPos != 0)
				{
					str.copy(p, pos - startPos - 1, startPos + 1);
					string str1(p, pos - startPos - 1);
					an.push_back(atoi(str1.c_str()));
				}
				startPos = pos;
			}
			else
			{
				str.copy(p, str.length() - startPos - 1, startPos + 1);
				string str1(p, str.length() - startPos - 1);
				an.push_back(atoi(str1.c_str()));
				break;
			}

		}
		m_answer.push_back(an);
		startPos = 0;
	}

}

void BPNN_Recommendation::trainingXY()
{
	double z = 0.0;
	for(double x = 0.0; x <= 1.0; x += 0.01)
	{
		if(x != 0.01)
			continue;
		for(double y = 0.0; y <= 1.0; y += 0.01)
		{
			if(y != 0.08)
				continue;
			z = 1 - x - y;
			double accu = 0.0;
			if(z >= 0)
			{
				int k = 0;

				for(int index = 0; index < m_userList.size(); index++)
				{
					for(k = 0; k < m_userList[index]->alternativeList.size(); k++)
					{
						m_userList[index]->alternativeList[k].weight[FINAL] = x * m_userList[index]->alternativeList[k].weight[SOCIAL] / m_userList[index]->maxWeght[SOCIAL] +
							y * m_userList[index]->alternativeList[k].weight[PERSONAL] / m_userList[index]->maxWeght[PERSONAL] + 
							z * m_userList[index]->alternativeList[k].weight[ITEM] / m_userList[index]->maxWeght[ITEM];
						/*
						if(index == 1 && k < 2)
						{
							cout << " So " << m_userList[index]->maxWeght[SOCIAL] << " pe " <<
								m_userList[index]->maxWeght[PERSONAL] << " it " << 
								m_userList[index]->maxWeght[ITEM] << endl;
						}
						*/
					}

					vector<WeightArticle> v = getTopN_Y(m_userList[index]->alternativeList, FINAL, TOP_N);

					int commom = 0;
					for(k = 0; k < m_answer[index].size(); k++)
					{
						for(int i = 0; i < m_answer[index].size(); i++)
						{
							if(v[k].id == m_answer[index][i])
								commom++;
						}
					}

					accu += (double)commom / m_answer[index].size();
				}
		
				accu = accu / m_userList.size();
				if(accu > accuracyCurr)
				{
					accuracyCurr = accu;
					m_y = y;
					m_x = x;
					m_accuracy = accuracyCurr;
					cout << "In trainingXY: " << accu << endl;
				}
				//else
					//cout << "In trainy: " << accu << " x " << x << " y " << y << endl;
				if(m_accuracy > accuracy)
					break;
			}
			else
				break;

		}
		if(m_accuracy > accuracy)
					break;
		if(z < 0)
			break;
	}

	cout << "train final accuracy: " << m_accuracy << endl;
	cout << "m_x: " << m_x << " m_y: " << m_y << " m_z " << 1 - m_x - m_y << endl;
	//write m_x m_y into file 
	WriteXYintoFile();
}

//write m_x m_y into file
void BPNN_Recommendation::WriteXYintoFile()
{
	ofstream outXY("xy.txt");
	if(outXY.fail())
	{
		cout << "ERROR: fail open the file xy.txt..." << endl;
		return;
	}

	outXY << m_x << endl;
	outXY << m_y << endl;

	outXY.close();
}

//read m_x m_y into file
void BPNN_Recommendation::ReadXYintoFile(string fileName)
{
	ifstream inXY(fileName);
	if(inXY.fail())
	{
		cout << "ERROR: fail open the file " << fileName << "..." << endl;
		return;
	}

	int count = 0;
	while(!inXY.eof())
	{
		string str("");
		getline(inXY, str);
		if(count == 0)
			m_x = atof(str.c_str());
		else 
		{
			m_y = atof(str.c_str());
			break;
		}
		count++;
	}

	inXY.close();
}

void BPNN_Recommendation::recommendArticle()
{
	cout << "Begin to get mix recommendation." << endl;
	
	for(int index = 0; index < m_userList.size(); index++)
	{
		for(int k = 0; k < m_userList[index]->alternativeList.size(); k++)
		{
			m_userList[index]->alternativeList[k].weight[FINAL] = m_x * m_userList[index]->alternativeList[k].weight[SOCIAL] / m_userList[index]->maxWeght[SOCIAL] +
				m_y * m_userList[index]->alternativeList[k].weight[PERSONAL] / m_userList[index]->maxWeght[PERSONAL] + 
				(1 - m_x - m_y) * m_userList[index]->alternativeList[k].weight[ITEM] / m_userList[index]->maxWeght[ITEM];
		}
	}
    
	cout << "mix recommendation completed." << endl;
}

void BPNN_Recommendation::training()
{
	ReadXYintoFile("xy.txt");
	
	//figure weight
	for(int i = 0; i < m_userList.size(); ++i){
		//input
		for(int k = 0; k < m_userList[i]->alternativeList.size(); k++)
		{
			m_userList[i]->alternativeList[k].weight[FINAL] = m_x * m_userList[i]->alternativeList[k].weight[SOCIAL] / m_userList[i]->maxWeght[SOCIAL] +
				m_y * m_userList[i]->alternativeList[k].weight[PERSONAL] / m_userList[i]->maxWeght[PERSONAL] + 
				(1 - m_x - m_y) * m_userList[i]->alternativeList[k].weight[ITEM] / m_userList[i]->maxWeght[ITEM];

			//max 
			if(m_userList[i]->maxWeght[FINAL] < m_userList[i]->alternativeList[k].weight[FINAL])
				m_userList[i]->maxWeght[FINAL] = m_userList[i]->alternativeList[k].weight[FINAL];
			m_userList[i]->maxWeght[FINAL] = (m_userList[i]->maxWeght[FINAL] == 0? 1.0 : m_userList[i]->maxWeght[FINAL]);
		}
	}

	vector <vector<double>> input, output;
	vector <double> curI, curO;
	//make input and output
	for(int i = 1; i <= CASENUM; ++i){
		curI.clear();
		curO.clear();
		
		//input
		for(int k = 0; k < m_userList[i - 1]->alternativeList.size(); k++)
		{
			m_userList[i - 1]->alternativeList[k].weight[FINAL] /= m_userList[i - 1]->maxWeght[FINAL];
			
			curI.push_back(m_userList[i - 1]->alternativeList[k].weight[FINAL]);

			//output
			bool isNum1 = false;
			for(int m = 0; m < m_answer[i - 1].size(); m++)
			{
				if(m_userList[i - 1]->alternativeList[k].id == m_answer[i - 1][m])
				{
					curO.push_back(1.0);
					isNum1 = true;
					break;
				}
			}

			if(!isNum1)
				curO.push_back(0.0);
		}

		while(curI.size() < NodeNum)
			curI.push_back(0.0);
		input.push_back(curI);

		while(curO.size() < NodeNum)
			curO.push_back(0.0);
		output.push_back(curO);
	}

	//printNNInput(input);
	//printNNOutput(output);
	
	//int neurons[3] = {8, 8, NodeNum};
	int neurons[3] = {20, 20, NodeNum};

	BPLearning NN(
		Network(NodeNum,3,new SigmodFunction(2),neurons),
		1,0.0
		);
	//NN.run(input[0],output[0]);
	for(int i = 0;i < TIME; ++i)
	{
		double error =  NN.runAll(input,output);
		printf("case %d's error is %lf\n", i, error);
		if(error < ACCURACY)
			break;
	}

	/********************save***********************/ 
	ofstream ou("NetModel//netWorkOutput.txt");   //netWork outPut
	if(ou.fail())
	{
		cout << "ERROR: fail to open file netWorkOutput.txt..." << endl;
		return;
	}

	for(int i = 0; i < NN.network.output.size(); i++)
		ou << NN.network.output[i] << endl;
	ou.close();

	ou.open("NetModel//laySum.txt"); // lay sum
	if(ou.fail())
	{
		cout << "ERROR: fail to open file laySum.txt..." << endl;
		return;
	}
	for(int i = 0; i < NN.network.layer.size(); i++)
		for(int k = 0; k < NN.network.layer[i].sum.size(); k++)
		{
			ou << NN.network.layer[i].sum[k] << endl;
		}
	ou.close();

	ou.open("NetModel//layOutput.txt"); // lay output
	if(ou.fail())
	{
		cout << "ERROR: fail to open file layOutput.txt..." << endl;
		return;
	}
	for(int i = 0; i < NN.network.layer.size(); i++)
		for(int k = 0; k < NN.network.layer[i].output.size(); k++)
			ou << NN.network.layer[i].output[k] << endl;
	ou.close();

	ou.open("NetModel//layNeuronOutput.txt"); // lay neuron output
	if(ou.fail())
	{
		cout << "ERROR: fail to open file layNeuronOutput.txt..." << endl;
		return;
	}

	for(int i = 0; i < NN.network.layer.size(); i++)
		for(int k = 0; k < NN.network.layer[i].neuron.size(); k++)
			ou << NN.network.layer[i].neuron[k].output << endl;
	ou.close();

	ou.open("NetModel//layNeuronThreshold.txt"); // lay neuron threshold
	if(ou.fail())
	{
		cout << "ERROR: fail to open file layNeuronThreshold.txt..." << endl;
		return;
	}
	for(int i = 0; i < NN.network.layer.size(); i++)
		for(int k = 0; k < NN.network.layer[i].neuron.size(); k++)
			ou << NN.network.layer[i].neuron[k].threshold << endl;
	ou.close();

	ou.open("NetModel//layNeuronWeight.txt"); // lay neuron weight
	if(ou.fail())
	{
		cout << "ERROR: fail to open file layNeuronWeight.txt..." << endl;
		return;
	}
	for(int i = 0; i < NN.network.layer.size(); i++)
		for(int k = 0; k < NN.network.layer[i].neuron.size(); k++)
			for(int j = 0; j < NN.network.layer[i].neuron[k].weight.size(); j++)
				ou << NN.network.layer[i].neuron[k].weight[j] << endl;
	ou.close();

	cout << "NN model completed! " << endl;
	/*
	//test
	vector <double> data;
	for(int i = 0; i < input[0].size(); i++)
		data.push_back(input[0][i]);

	vector <double> res = NN.calc(data);
	for(int i=0;i<(int)res.size();++i)
		cout<< res[i] << " ";
	cout << endl;
	*/
}

void BPNN_Recommendation::recommendArticleByBP()
{
	cout << "Compute NN model. " << endl;
	//first compute the model
	int neurons[3] = {20, 20, NodeNum};

	BPLearning NN(
		Network(NodeNum,3,new SigmodFunction(2),neurons),
		1,0.0
		);

	ifstream in("NetModel//netWorkOutput.txt");   //netWork outPut
	if(in.fail())
	{
		cout << "ERROR: fail to open file netWorkOutput.txt..." << endl;
		return;
	}

	for(int i = 0; i < NN.network.output.size(); i++)
		in >> NN.network.output[i];
	in.close();

	in.open("NetModel//laySum.txt"); // lay sum
	if(in.fail())
	{
		cout << "ERROR: fail to open file laySum.txt..." << endl;
		return;
	}
	for(int i = 0; i < NN.network.layer.size(); i++)
		for(int k = 0; k < NN.network.layer[i].sum.size(); k++)
		{
			in >>  NN.network.layer[i].sum[k];
		}
	in.close();

	in.open("NetModel//layOutput.txt"); // lay output
	if(in.fail())
	{
		cout << "ERROR: fail to open file layOutput.txt..." << endl;
		return;
	}
	for(int i = 0; i < NN.network.layer.size(); i++)
		for(int k = 0; k < NN.network.layer[i].output.size(); k++)
			in >> NN.network.layer[i].output[k];
	in.close();

	in.open("NetModel//layNeuronOutput.txt"); // lay neuron output
	if(in.fail())
	{
		cout << "ERROR: fail to open file layNeuronOutput.txt..." << endl;
		return;
	}

	for(int i = 0; i < NN.network.layer.size(); i++)
		for(int k = 0; k < NN.network.layer[i].neuron.size(); k++)
			in >> NN.network.layer[i].neuron[k].output;
	in.close();

	in.open("NetModel//layNeuronThreshold.txt"); // lay neuron threshold
	if(in.fail())
	{
		cout << "ERROR: fail to open file layNeuronThreshold.txt..." << endl;
		return;
	}
	for(int i = 0; i < NN.network.layer.size(); i++)
		for(int k = 0; k < NN.network.layer[i].neuron.size(); k++)
			in >> NN.network.layer[i].neuron[k].threshold;
	in.close();

	in.open("NetModel//layNeuronWeight.txt"); // lay neuron weight
	if(in.fail())
	{
		cout << "ERROR: fail to open file layNeuronWeight.txt..." << endl;
		return;
	}
	for(int i = 0; i < NN.network.layer.size(); i++)
		for(int k = 0; k < NN.network.layer[i].neuron.size(); k++)
			for(int j = 0; j < NN.network.layer[i].neuron[k].weight.size(); j++)
				in >> NN.network.layer[i].neuron[k].weight[j];
	in.close();

	cout << "NN model completed! " << endl;

	//get input
	ReadXYintoFile("xy.txt");
	
	//figure weight
	for(int i = 0; i < m_userList.size(); ++i){
		//input
		for(int k = 0; k < m_userList[i]->alternativeList.size(); k++)
		{
			m_userList[i]->alternativeList[k].weight[FINAL] = m_x * m_userList[i]->alternativeList[k].weight[SOCIAL] / m_userList[i]->maxWeght[SOCIAL] +
				m_y * m_userList[i]->alternativeList[k].weight[PERSONAL] / m_userList[i]->maxWeght[PERSONAL] + 
				(1 - m_x - m_y) * m_userList[i]->alternativeList[k].weight[ITEM] / m_userList[i]->maxWeght[ITEM];

			//max 
			if(m_userList[i]->maxWeght[FINAL] < m_userList[i]->alternativeList[k].weight[FINAL])
				m_userList[i]->maxWeght[FINAL] = m_userList[i]->alternativeList[k].weight[FINAL];
			m_userList[i]->maxWeght[FINAL] = (m_userList[i]->maxWeght[FINAL] == 0? 1.0 : m_userList[i]->maxWeght[FINAL]);
		}
	}

	vector <double> curI;
	double accu = 0.0;
	//make input and figure output
	for(int i = 1; i <= CASENUM; ++i){
		curI.clear();
		
		//input
		for(int k = 0; k < m_userList[i - 1]->alternativeList.size(); k++)
		{
			m_userList[i - 1]->alternativeList[k].weight[FINAL] /= m_userList[i - 1]->maxWeght[FINAL];
			
			curI.push_back(m_userList[i - 1]->alternativeList[k].weight[FINAL]);
		}

		while(curI.size() < NodeNum)
			curI.push_back(0.0);
		
		//figure output
		vector <double> outp = NN.calc(curI);
		/*
		if(i == 1)
		{
			cout << "size: " << outp.size() << endl;
			for(int k = 0; k < outp.size(); k++)
				cout << outp[k] << " ";
			cout << endl;
			//break;
		}
		cout << endl << endl;
		*/

		//compute weight
		for(int m = 0; m < m_userList[i - 1]->alternativeList.size(); m++)
		{
			outp[m] = (1.0 - outp[m] > 0 ? 1.0 - outp[m] : outp[m] - 1.0);
			//if(i == 1)
				//cout << outp[m] << " ";
			//cout << endl << endl;
			m_userList[i - 1]->alternativeList[m].weight[FINAL] = 10.0 - outp[m];
		}
		/*
		if(i == 1)
		{
			for(int k = 0; k < m_userList[i - 1]->alternativeList.size(); k++)
				cout << m_userList[i - 1]->alternativeList[k].weight[FINAL] << " ";
			cout << endl;
			break;
		}
		*/

		//figure accuracy
		vector<WeightArticle> v = getTopN_Y(m_userList[i - 1]->alternativeList, FINAL, TOP_N);
		/*
		if(i == 1)
		{
			cout << "v" << endl;
			for(int k = 0; k < v.size(); k++)
				cout << v[k].id << " " << v[k].weight[FINAL] << endl;
		}
		*/
		int commom = 0;
		for(int k = 0; k < m_answer[i - 1].size(); k++)
		{
			for(int j = 0; j < m_answer[i - 1].size(); j++)
			{
				if(v[k].id == m_answer[i - 1][j])
					commom++;
			}
		}

		accu += (double)commom / m_answer[i - 1].size();
	}

	accu /= m_userList.size();
	cout << "NN model accuracy: " << accu << endl;

}


/************************************************************************
*Debug method
*************************************************************************/

void BPNN_Recommendation::showAnswer()
{
	for(int k = 0; k < m_answer.size(); k++)
	{
		for(int j = 0; j < m_answer[k].size(); j++)
			cout << m_answer[k][j] << " ";
		cout << endl;

		if(k == 5)
			break;
	}
}

void BPNN_Recommendation::printNNInput(vector<vector<double>>& input)
{
	ofstream ou("Input.txt");
	if(ou.fail())
	{
		cout << "ERROR: fail to open Input.txt..." << endl;
		return;
	}

	for(int k = 0; k < input.size(); k++)
	{
		for(int i = 0; i < input[k].size(); i++)
			ou << input[k][i] << " ";
		ou << "\n";
	}

	ou.close();
}

void BPNN_Recommendation::printNNOutput(vector<vector<double>>& output)
{
	ofstream ou("Output.txt");
	if(ou.fail())
	{
		cout << "ERROR: fail to open Output.txt..." << endl;
		return;
	}

	for(int k = 0; k < output.size(); k++)
	{
		for(int i = 0; i < output[k].size(); i++)
			ou << output[k][i] << " ";
		ou << "\n";
	}

	ou.close();
}