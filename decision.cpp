#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <map>
#include <sstream>
#include <unordered_map>
#include <nlohmann/json.hpp> // JSON library for C++

using json = nlohmann::json;

using namespace std;

class Table {
public:
    vector<string> attrName;                    // stores attribute names.
    vector<vector<string>> data;                // store the actual data rows.
    vector<vector<string>> attrValueList;       // store unique attribute values for each attribute.

    
    /* `extractAttrValue()` : Extracts unique attribute values for each attribute from the `data` and 
    stores them in `attrValueList`. */

    void extractAttrValue() {
        attrValueList.resize(attrName.size());
        for (int j = 0; j < attrName.size(); j++) {
            map<string, int> value;
            for (int i = 0; i < data.size(); i++) {
                value[data[i][j]] = 1;
            }
            for (auto iter = value.begin(); iter != value.end(); iter++) {
                attrValueList[j].push_back(iter->first);
            }
        }
    }
};

// characteristics of each node in a decision tree
class Node {
public:
    int criteriaAttrIndex;          // stores index of the attribute that the node splits on.
    string attrValue;               // stores the value of the attribute that leads to this node.
    int treeIndex;                  // stores the index of the node in decision tree
    bool isLeaf;                    // Indicates if the node is a leaf node
    string label;                   // Label (or class) assigned to the leaf node
    vector<int> children;           // Vector of indices of child nodes


    Node() {
        isLeaf = false;
    }
};

class DecisionTree {
public:
    Table initialTable;             // Stores the initial table of data.
    vector<Node> tree;              // Vector of `Node` objects representing the decision tree.

    /*Takes a Table object as input, initializes initialTable, extracts attribute values,
     builds the decision tree starting from the root node (run() is called).*/

    DecisionTree(Table table) {
        initialTable = table;
        initialTable.extractAttrValue();

        Node root;
        root.treeIndex = 0;
        tree.push_back(root);
        run(initialTable, 0);
        printTree(0, "");
    }

    // `guess()`: Predicts the label for a given input row using DFS traversal.
    string guess(vector<string> row) {
        string label = "";
        int leafNode = dfs(row, 0);
        if (leafNode == -1) {
            return "dfs failed";
        }
        label = tree[leafNode].label;
        return label;
    }

    /*dfs() function recursively traverses a decision tree to find the appropriate leaf node that 
    corresponds to a given row of data for classification.*/
    int dfs(vector<string>& row, int here) {
        if (tree[here].isLeaf) {
            return here;
        }

        int criteriaAttrIndex = tree[here].criteriaAttrIndex;
        for (int i = 0; i < tree[here].children.size(); i++) {
            int next = tree[here].children[i];
            if (row[criteriaAttrIndex] == tree[next].attrValue) {
                return dfs(row, next);
            }
        }
        return -1;
    }

    /*
    
    run() function: recursively constructs a decision tree using the ID3 algorithm.
    It selects attributes based on information gain, splits the data into subsets, 
    creates nodes for each subset, and assigns labels to leaf nodes based on majority voting, 
    ensuring the tree grows until all data subsets are classified or a stopping criterion 
    (such as high purity in nodes) is met.
    
    */

    void run(Table table, int nodeIndex) {
        if (isLeafNode(table)) {
            tree[nodeIndex].isLeaf = true;
            tree[nodeIndex].label = table.data.back().back();
            return;
        }

        int selectedAttrIndex = getSelectedAttribute(table);
        map<string, vector<int>> attrValueMap;
        for (int i = 0; i < table.data.size(); i++) {
            attrValueMap[table.data[i][selectedAttrIndex]].push_back(i);
        }

        tree[nodeIndex].criteriaAttrIndex = selectedAttrIndex;
        pair<string, int> majority = getMajorityLabel(table);
        if ((double)majority.second / table.data.size() > 0.8) {
            tree[nodeIndex].isLeaf = true;
            tree[nodeIndex].label = majority.first;
            return;
        }

        for (int i = 0; i < initialTable.attrValueList[selectedAttrIndex].size(); i++) {
            string attrValue = initialTable.attrValueList[selectedAttrIndex][i];
            Table nextTable;
            vector<int> candi = attrValueMap[attrValue];
            for (int i = 0; i < candi.size(); i++) {
                nextTable.data.push_back(table.data[candi[i]]);
            }

            Node nextNode;
            nextNode.attrValue = attrValue;
            nextNode.treeIndex = (int)tree.size();
            tree[nodeIndex].children.push_back(nextNode.treeIndex);
            tree.push_back(nextNode);

            if (nextTable.data.size() == 0) {
                nextNode.isLeaf = true;
                nextNode.label = getMajorityLabel(table).first;
                tree[nextNode.treeIndex] = nextNode;
            } else {
                run(nextTable, nextNode.treeIndex);
            }
        }
    }


    /*
    getMajorityLabel() function: computes the majority label and its count from the last column of a given `Table` object 
    (`table`). It iterates through the data rows, counts occurrences of each label, and determines which label 
    has the highest count, returning this label along with its count as a pair<string, int>.
    
    */
    pair<string, int> getMajorityLabel(Table table) {
        string majorLabel = "";
        int majorCount = 0;
        map<string, int> labelCount;
        for (int i = 0; i < table.data.size(); i++) {
            labelCount[table.data[i].back()]++;
            if (labelCount[table.data[i].back()] > majorCount) {
                majorCount = labelCount[table.data[i].back()];
                majorLabel = table.data[i].back();
            }
        }
        return {majorLabel, majorCount};
    }

    /*
    isLeafNode() function: checks if all rows in the Table object (table) have the same label in the last column.
    If all rows except the first have the same label, it returns true, indicating that the node is a leaf node in 
    the context of constructing a decision tree. If there is any difference in labels, it returns false.
    */

    bool isLeafNode(Table table) {
        for (int i = 1; i < table.data.size(); i++) {
            if (table.data[0].back() != table.data[i].back()) {
                return false;
            }
        }
        return true;
    }

    /*
    `getSelectedAttribute()` function selects the attribute (column index) from a given `Table` object (`table`)
    that maximizes the gain ratio when used as the splitting criterion in a decision tree. It iterates through the
    attributes (excluding the last column assumed to be the label) and computes their gain ratios, returning the index
    of the attribute with the highest gain ratio.
    */

    int getSelectedAttribute(Table table) {
        int maxAttrIndex = -1;
        double maxAttrValue = 0.0;
        for (int i = 0; i < initialTable.attrName.size() - 1; i++) {
            if (maxAttrValue < getGainRatio(table, i)) {
                maxAttrValue = getGainRatio(table, i);
                maxAttrIndex = i;
            }
        }
        return maxAttrIndex;
    }

    /*
    `getGainRatio()` function calculates the gain ratio for a specific attribute (`attrIndex`) in a given 
    `Table` object (`table`). It divides the information gain (`getGain(table, attrIndex)`) by the split information 
    (`getSplitInfoAttrD(table, attrIndex)`) to determine the effectiveness of the attribute in reducing uncertainty in 
    the decision tree algorithm.
    */    

    double getGainRatio(Table table, int attrIndex) {
        return getGain(table, attrIndex) / getSplitInfoAttrD(table, attrIndex);
    }

    /*
    `getInfoD()` function: calculates the entropy (information content) of the labels (last column)
    in a given `Table` object (`table`). It computes the entropy using Shannon's entropy formula for discrete probability 
    distributions, iterating over the data to determine the probability of each label and then calculating its 
    contribution to the overall entropy.
    
    */    

    double getInfoD(Table table) {
        double ret = 0.0;
        int itemCount = (int)table.data.size();
        map<string, int> labelCount;
        for (int i = 0; i < table.data.size(); i++) {
            labelCount[table.data[i].back()]++;
        }
        for (auto iter = labelCount.begin(); iter != labelCount.end(); iter++) {
            double p = (double)iter->second / itemCount;
            ret += -1.0 * p * log(p) / log(2);
        }
        return ret;
    }

    /*
    
    `getInfoAttrD()` function: calculates the expected entropy (information content) of a given attribute (`attrIndex`) 
    in a `Table` object (`table`). It computes this by summing the weighted entropy contributions of each distinct 
    attribute value, where the weight is proportional to the frequency of each value in the data set.

    */

    double getInfoAttrD(Table table, int attrIndex) {
        double ret = 0.0;
        int itemCount = (int)table.data.size();
        map<string, vector<int>> attrValueMap;
        for (int i = 0; i < table.data.size(); i++) {
            attrValueMap[table.data[i][attrIndex]].push_back(i);
        }
        for (auto iter = attrValueMap.begin(); iter != attrValueMap.end(); iter++) {
            Table nextTable;
            for (int i = 0; i < iter->second.size(); i++) {
                nextTable.data.push_back(table.data[iter->second[i]]);
            }
            int nextItemCount = (int)nextTable.data.size();
            ret += (double)nextItemCount / itemCount * getInfoD(nextTable);
        }
        return ret;
    }

    /*
    
    `getGain()` function: calculates the information gain achieved by splitting the data in a `Table` object (`table`)
    based on a specified attribute (`attrIndex`). It quantifies how much uncertainty about the final outcome (entropy) 
    decreases after splitting the data according to the attribute, by subtracting the expected entropy of the attribute 
    (`getInfoAttrD(table, attrIndex)`) from the overall entropy (`getInfoD(table)`).
    
    */

    double getGain(Table table, int attrIndex) {
        return getInfoD(table) - getInfoAttrD(table, attrIndex);
    }

    /*
    
    `getSplitInfoAttrD()` function: calculates the split information for a given attribute (`attrIndex`) in a `Table` 
    object (`table`). It measures the amount of uncertainty associated with the distribution of attribute values across 
    the dataset, using Shannon's entropy formula to compute the entropy of the probability distribution of attribute 
    values.
    
    */

    double getSplitInfoAttrD(Table table, int attrIndex) {
        double ret = 0.0;
        int itemCount = (int)table.data.size();
        map<string, vector<int>> attrValueMap;
        for (int i = 0; i < table.data.size(); i++) {
            attrValueMap[table.data[i][attrIndex]].push_back(i);
        }
        for (auto iter = attrValueMap.begin(); iter != attrValueMap.end(); iter++) {
            Table nextTable;
            for (int i = 0; i < iter->second.size(); i++) {
                nextTable.data.push_back(table.data[iter->second[i]]);
            }
            int nextItemCount = (int)nextTable.data.size();
            double d = (double)nextItemCount / itemCount;
            ret += -1.0 * d * log(d) / log(2);
        }
        return ret;
    }

    // printTree(): Prints the decision tree in a readable format.
    void printTree(int nodeIndex, string branch) {
        if (tree[nodeIndex].isLeaf) {
            cout << branch << "Label: " << tree[nodeIndex].label << "\n";
        }
        for (int i = 0; i < tree[nodeIndex].children.size(); i++) {
            int childIndex = tree[nodeIndex].children[i];
            string attributeName = initialTable.attrName[tree[nodeIndex].criteriaAttrIndex];
            string attributeValue = tree[childIndex].attrValue;
            printTree(childIndex, branch + attributeName + " = " + attributeValue + ", ");
        }
    }

    // Method to serialize the decision tree to JSON
    json serializeTreeToJson() {
        json treeJson;
        for (const Node& node : tree) {
            json nodeJson;
            nodeJson["criteriaAttrIndex"] = node.criteriaAttrIndex;
            nodeJson["attrValue"] = node.attrValue;
            nodeJson["treeIndex"] = node.treeIndex;
            nodeJson["isLeaf"] = node.isLeaf;
            nodeJson["label"] = node.label;
            nodeJson["children"] = node.children;
            treeJson.push_back(nodeJson);
        }
        return treeJson;
    }
};

/*

`InputReader` class is designed to read data from a CSV file (`filename`) and parse it into a `Table` object. 
It opens the file, reads each line, splits it by comma to extract individual values, and then categorizes the data into 
attribute names (`attrName`) and data rows (`data`).

*/
class InputReader {
private:
    ifstream fin;           // stores input file stream
    Table table;            // stores data that is read from the file.
public:
    InputReader(string filename) {
        fin.open(filename);
        if (!fin) {
            cout << filename << " file could not be opened\n";
            exit(1);
        }
        string line;
        bool isAttrName = true;
        while (getline(fin, line)) {
            vector<string> row;
            stringstream ss(line);
            string item;
            while (getline(ss, item, ',')) {
                row.push_back(item);
            }
            if (isAttrName) {
                table.attrName = row;
                isAttrName = false;
            } else {
                table.data.push_back(row);
            }
        }
        fin.close();
    }

    Table getTable() {
        return table;
    }
};

/*
main program reads the csv file, gets the data, trains the decision tree model on the data and dumps the trained model
into json file.
*/

int main(int argc, char* argv[]) {
    InputReader inputReader("Crop_recommendation.csv");
    Table table = inputReader.getTable();

    DecisionTree decisionTree(table);

    // Save the decision tree to a JSON file
    ofstream fout("crop_prediction.json");
    fout << decisionTree.serializeTreeToJson().dump(4);  // Pretty-print with indentation of 4 spaces
    fout.close();

    return 0;
}
