// 题目：216. 组合总和 III（Combination Sum III）
// 核心思路：回溯枚举 1..9 中递增选择的数字，用剩余和 s 与已选个数两个约束做剪枝，凑满 k 个且 s 为 0 时收集答案。
// 时间复杂度：O(C(9,k)) 量级，回溯树上每个合法组合被访问一次；空间复杂度：O(k)，递归深度与路径长度。
class Solution {  // LeetCode 约定的题解类
public:  // 对外接口
    vector<vector<int>> combinationSum3(int k, int n) {  // 在 1..9 中选 k 个互不相同的数使其和为 n，返回所有组合
        vector<vector<int>> ans;  // 存放所有合法组合
        vector<int> t;  // 当前递归路径上已选中的数字
        function<void(int, int)> dfs = [&](int i, int s) {  // i：下一个可选的数（只能从 i 起选）；s：还需要凑出的剩余和
            if (s == 0) {  // 剩余和为 0，说明已经凑够
                if (t.size() == k) {  // 并且恰好选了 k 个数，才是一个合法方案
                    ans.emplace_back(t);  // 把当前路径复制一份放进答案（t 后面还会被修改）
                }  // if 结束
                return;  // 和为 0 后再加数只会超出，直接回溯
            }  // if 结束
            if (i > 9 || i > s || t.size() >= k) {  // 三种剪枝：数字超过 9 / 最小可选数已超过剩余和 / 已经选够 k 个
                return;  // 该分支不可能再有解，回溯
            }  // if 结束
            t.emplace_back(i);  // 选择数字 i
            dfs(i + 1, s - i);  // 递归：下一个数只能从 i+1 起选（保证递增、不重复），剩余和减去 i
            t.pop_back();  // 撤销选择 i，恢复现场
            dfs(i + 1, s);  // 不选 i，直接考虑下一个数
        };  // lambda 定义结束
        dfs(1, n);  // 从数字 1 开始，目标是凑出 n
        return ans;  // 返回全部方案
    }  // 方法结束
};  // 类定义结束