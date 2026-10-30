// 题目：842. 将数组拆分成斐波那契序列（Split Array into Fibonacci Sequence）
// 思路：回溯枚举前两个数，之后每个切出的数必须恰好等于前两个数之和；用 INT_MAX 与前缀和剪枝。
// 时间复杂度：O(n^2) 量级的回溯搜索，n 为数字串长度；空间复杂度：O(n)，答案数组与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> splitIntoFibonacci(string num) {  // num 是只含数字的字符串；返回拆出的斐波那契序列，拆不出时返回空数组
        int n = num.size();  // 数字串长度，dfs 中反复使用
        vector<int> ans;  // 保存当前正在构造的拆分结果
        function<bool(int)> dfs = [&](int i) -> bool {  // dfs(i) 表示从下标 i 开始继续往后切分，返回是否已找到合法拆分
            if (i == n) {  // 已经切到字符串末尾
                return ans.size() > 2;  // 斐波那契序列至少要有 3 个数，此时检查长度是否大于 2
            }  // 末尾判断结束
            long long x = 0;  // 当前要切出的数，用 long long 防止累加时溢出
            for (int j = i; j < n; ++j) {  // 枚举以 i 开头的数的结束位置 j
                if (j > i && num[i] == '0') {  // 多位数不能有前导零：首位是 '0' 且长度大于 1 时非法
                    break;  // 直接 break，让外层回溯换一种切法
                }  // 前导零判断结束
                x = x * 10 + num[j] - '0';  // 把第 j 位数字接到当前数末尾
                if (x > INT_MAX || (ans.size() > 1 && x > (long long) ans[ans.size() - 1] + ans[ans.size() - 2])) {  // 超过 int 上限，或已大于前两个数之和，继续加长只会更大，剪枝
                    break;  // 跳出内层循环
                }  // 溢出/超和判断结束
                if (ans.size() < 2 || x == (long long) ans[ans.size() - 1] + ans[ans.size() - 2]) {  // 前两个数可以任选；之后必须满足 x 等于前两项之和
                    ans.push_back(x);  // 把 x 作为下一个数压入答案
                    if (dfs(j + 1)) {  // 从 j + 1 继续切分，成功则整条路径都保留
                        return true;  // 找到完整合法拆分，立即向上返回成功
                    }  // 递归失败分支结束
                    ans.pop_back();  // 回溯：弹出 x，恢复现场后再尝试其他切法
                }  // 候选 x 处理结束
            }  // 内层切分尝试结束
            return false;  // 本次递归返回失败
        };  // lambda 定义结束，dfs 已能递归调用自身
        dfs(0);  // 从下标 0 开始切分
        return ans;  // 成功时 ans 就是答案；失败时 ans 已被回溯清空
    }  // 方法结束
};  // 类定义结束