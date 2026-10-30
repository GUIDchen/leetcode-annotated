// 题目：1286. 字母组合迭代器（Iterator for Combination）
// 思路：构造时用 DFS 按字典序枚举所有长度为 combinationLength 的下标组合并缓存，next 与 hasNext 只做数组下标访问。
// 时间复杂度：构造 O(C(n,k)·k)，每个组合要拼接 k 个字符；next/hasNext 为 O(1)；空间复杂度：O(C(n,k)·k)，缓存全部组合。
class CombinationIterator {  // 字母组合迭代器：按字典序逐个产出定长组合
public:  // 以下成员对外可见
    string characters;  // 原字符串，下标从小到大取字符即可保证字典序
    vector<string> cs;  // 缓存所有长度为 combinationLength 的组合，按顺序存放
    int idx;  // 当前 next 应返回的组合下标
    int n;  // 原字符串长度
    int combinationLength;  // 每个组合需要取的字符个数
    string t;  // DFS 过程中的「正在进行中的组合」

    CombinationIterator(string characters, int combinationLength) {  // 构造函数：characters 为字符集，combinationLength 为组合长度
        idx = 0;  // 结果下标从 0 开始
        n = characters.size();  // 记录字符集长度，供 DFS 判断边界
        this->characters = characters;  // 保存字符集到成员变量（同名参数遮盖了成员，故用 this->）
        this->combinationLength = combinationLength;  // 保存组合长度到成员变量（同样用 this-> 区分同名参数）
        dfs(0);  // 从下标 0 开始 DFS，预先生成全部组合
    }

    string next() {  // 返回下一个组合，并让内部下标前移
        return cs[idx++];  // 先取当前组合，再把下标自增 1（后置 ++）
    }

    bool hasNext() {  // 是否还有未返回的组合
        return idx < cs.size();  // 下标尚未越界就说明还有组合
    }

    void dfs(int i) {  // 深度优先搜索：i 是下一个可选的字符下标
        if (t.size() == combinationLength) {  // 已选够 k 个字符，得到一个完整组合
            cs.push_back(t);  // 把当前组合加入缓存
            return;  // 递归出口：不再继续向下选择
        }
        if (i == n) return;  // 可用下标用尽，剪枝返回
        t.push_back(characters[i]);  // 分支一：选择第 i 个字符
        dfs(i + 1);  // 继续从 i + 1 开始选后面的字符
        t.pop_back();  // 回溯：撤销刚才的选择，恢复状态
        dfs(i + 1);  // 分支二：不选第 i 个字符，直接从 i + 1 继续
    }
};  // 迭代器类定义结束

/**  // 以下为 LeetCode 提供的调用示例注释（原样保留）
 * Your CombinationIterator object will be instantiated and called as such:
 * CombinationIterator* obj = new CombinationIterator(characters, combinationLength);
 * string param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */