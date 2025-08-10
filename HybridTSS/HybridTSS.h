#ifndef HYBRIDTSSV1_2_HYBRIDTSS_H
#define HYBRIDTSSV1_2_HYBRIDTSS_H
#include "SubHybridTSS.h"
using namespace std;
class HybridTSS : public PacketClassifier {
public:
    // 父类方法
    HybridTSS();
    void ConstructClassifier(const std::vector<Rule> &rules) override;

    int ClassifyAPacket(const Packet& packet) override;
    void DeleteRule(const Rule& rule) override;
    void InsertRule(const Rule& rule) override;
    Memory MemSizeBytes() const override;
    int MemoryAccess() const override;
    size_t NumTables() const override;
    size_t RulesInTable(size_t tableIndex) const override;

    // 子类方法与冗余函数
    string funName() override {
        return "class: HybridTSS";
    }
    string prints() {
        return "";
    }

    void printInfo();
    vector<int> getAction(SubHybridTSS *state, int epsilion);
    void ConstructBaseline(const vector<Rule> &rules);


private:
    int binth = 8;
    SubHybridTSS *root;
    double rtssleaf = 1.5;
    vector<vector<double> > QTable;

    // epsilon-greedy 動態控制
    double epsilon; 
    const double epsilon_min = 0.05;
    const double epsilon_max = 1.0;
    const double epsilon_decay_k = 0.0005; // 衰減速度

    void train(const vector<Rule> &rules);
    void updateEpsilon(int step);
};
#endif //HYBRIDTSSV1_2_HYBRIDTSS_H
