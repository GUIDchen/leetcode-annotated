class Trie {  // 字典树节点：节点深度对应前缀长度，v 存该前缀下最多 3 个产品下标
public:  // 插入与查询接口对外公开
    void insert(string& w, int i) {  // 把第 i 个产品单词 w 沿字符逐层插入字典树
        Trie* node = this;  // 指针从根节点开始向下走
        for (int j = 0; j < w.size(); ++j) {  // 逐字符遍历，保证 w 的每个前缀节点都被访问到
            int idx = w[j] - 'a';  // 字符减去 'a' 得到 0..25 的孩子槽位
            if (!node->children[idx]) {  // 该字符对应的孩子还没建出来
                node->children[idx] = new Trie();  // 新建子节点，把这条前缀路径补全
            }  // 结束 if 块
            node = node->children[idx];  // 沿当前字符下移到前缀节点
            if (node->v.size() < 3) {  // 每个前缀最多只需要 3 个推荐，多存无益
                node->v.push_back(i);  // 记录产品下标；products 已排序，下标升序即字典序
            }  // 结束 if 块
        }  // 结束 for 循环
    }  // 插入完成

    vector<vector<int>> search(string& w) {  // 返回 searchWord 每个前缀对应的产品下标列表
        Trie* node = this;  // 从根节点开始匹配前缀
        int n = w.size();  // searchWord 的长度就是要返回的列表个数
        vector<vector<int>> ans(n);  // 按前缀个数开好答案数组，没匹配到的前缀保持为空
        for (int i = 0; i < w.size(); ++i) {  // 逐字符拼出 searchWord 的每一个前缀
            int idx = w[i] - 'a';  // 字符映射为 0..25 的下标
            if (!node->children[idx]) {  // 字典树里已经不存在这个前缀
                break;  // 更长的前缀必然也不存在，直接跳出循环
            }  // 结束 if 块
            node = node->children[idx];  // 下移到当前前缀节点
            ans[i] = move(node->v);  // 取出该前缀的候选下标，move 转移避免深拷贝
        }  // 结束 for 循环
        return ans;  // 返回每个前缀的推荐结果
    }  // search 方法结束

private:  // 私有成员：孩子指针数组与候选产品下标
    vector<Trie*> children = vector<Trie*>(26);  // 26 个小写字母对应的孩子指针，默认全为 nullptr
    vector<int> v;  // 该前缀下按字典序排好的产品下标，最多 3 个
};  // Trie 类定义结束

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {  // products：待搜索的商品列表；searchWord：用户逐字输入的搜索词
        sort(products.begin(), products.end());  // 先按字典序排序，保证每个前缀取到的都是最小的 3 个
        Trie* trie = new Trie();  // 建立字典树的根节点
        for (int i = 0; i < products.size(); ++i) {  // 枚举每个商品，把它的下标插入字典树
            trie->insert(products[i], i);  // 插入 products[i]，同时带上它的下标 i
        }  // 结束建树循环
        vector<vector<string>> ans;  // 存放最终结果：每个前缀一个推荐列表
        for (auto& v : trie->search(searchWord)) {  // 依次取出 searchWord 每个前缀的候选下标
            vector<string> t;  // 把下标翻译成商品字符串
            for (int i : v) {  // 遍历该前缀下的候选下标
                t.push_back(products[i]);  // 按下标取出商品名，放进临时列表
            }  // 结束内层循环
            ans.push_back(move(t));  // 把临时列表转移到答案里，省去一次拷贝
        }  // 结束外层循环
        return ans;  // 返回全部前缀的推荐结果
    }  // suggestedProducts 方法结束
};  // Solution 类定义结束