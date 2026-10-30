// 题目：2375. 根据模式串构造最小数字（Construct Smallest Number From DI String）
// 思路：从高位到低位按 1..9 升序 DFS 填入未使用的数字，用 pattern 的 I/D 约束剪枝，先搜到的解即字典序最小。
// 时间复杂度：最坏 O(9!) 枚举全排列，实际被约束强剪枝；空间复杂度：O(n)，递归深度与 vis/t 都同阶。
class Solution {  // LeetCode 约定的题解类
public:  // 题解成员对外可见
    string ans = "";  // 最终答案；为空串表示还没有找到解
    string pattern;  // 保存模式串，供 dfs 按下标取约束
    vector<bool> vis;  // vis[d] 表示数字 d 是否已在当前排列中使用
    string t = "";  // 当前正在构造的排列（字符形式）

    string smallestNumber(string pattern) {  // pattern 只包含 'I' 与 'D'
        this->pattern = pattern;  // 存到成员变量，递归函数里可直接读取
        vis.assign(10, false);  // 数字 1..9 的使用标记，多开一位让下标与数字对齐
        dfs(0);  // 从第 0 位开始搜索
        return ans;  // 返回字典序最小的合法数字串
    }

    void dfs(int u) {  // u 表示当前要填写的下标位置
        if (ans != "") return;  // 已经找到最优解，后续搜索全部直接返回
        if (u == pattern.size() + 1) {  // 位数 = 模式长度 + 1，说明数字已填满
            ans = t;  // 记录这组解
            return;
        }
        for (int i = 1; i < 10; ++i) {  // 按从小到大枚举，字典序更小的排列先被尝试
            if (!vis[i]) {  // 数字 i 还没有被使用
                if (u && pattern[u - 1] == 'I' && t.back() - '0' >= i) continue;  // I 要求上升，故 i 必须更大
                if (u && pattern[u - 1] == 'D' && t.back() - '0' <= i) continue;  // D 要求下降，故 i 必须更小
                vis[i] = true;  // 标记数字 i 已被使用
                t += to_string(i);  // 把 i 追加到当前排列末尾
                dfs(u + 1);  // 递归填写下一位
                t.pop_back();  // 回溯：撤销刚追加的字符
                vis[i] = false;  // 回溯：释放数字 i
            }
        }
    }
};