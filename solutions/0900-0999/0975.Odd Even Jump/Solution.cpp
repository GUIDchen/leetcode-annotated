// 题目：975. 奇偶跳（Odd Even Jump）
// 思路：逆序扫描有序表预处理出每个位置奇/偶跳的落点，再记忆化搜索每个起点能否跳到末尾。
// 时间复杂度：O(n log n)，建表 O(n log n) + 记忆化 O(n)；空间复杂度：O(n)，两个转移表与记忆数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int oddEvenJumps(vector<int>& arr) {  // arr：输入数组，返回能跳到末尾的下标个数
        int n = arr.size();  // n 为数组长度
        map<int, int> d;  // d 是「值 → 下标」的有序映射，逆序遍历时保存右侧已处理的元素
        int f[n][2];  // f[i][k] 记忆化：从 i 出发、下一步是 k 类跳（1 奇数跳 / 0 偶数跳）能否到达末尾
        int g[n][2];  // g[i][k] 预处理：从 i 出发、k 类跳的落点下标，-1 表示跳不了
        memset(f, 0, sizeof(f));  // f 全部初始化为 0，0 表示「还没计算过」
        for (int i = n - 1; ~i; --i) {  // 从右往左遍历，保证查表时右侧元素都已就位
            auto it = d.lower_bound(arr[i]);  // 奇数跳要跳到右侧不小于 arr[i] 的最小值，lower_bound 找第一个 >= arr[i] 的位置
            g[i][1] = it == d.end() ? -1 : it->second;  // 找不到说明无法跳（-1），否则取该值对应的下标
            it = d.upper_bound(arr[i]);  // 偶数跳要跳到右侧不大于 arr[i] 的最大值，先 upper_bound 再前移一位
            g[i][0] = it == d.begin() ? -1 : prev(it)->second;  // 已经是 begin 说明没有更小的值，无法跳
            d[arr[i]] = i;  // 把当前值及其下标放入有序表，供更左侧的元素查询
        }  // for 循环结束
        function<int(int, int)> dfs = [&](int i, int k) -> int {  // 记忆化搜索 lambda：k=1 表示下一步是奇数跳，k=0 表示偶数跳
            if (i == n - 1) {  // 已经到达末尾，说明这条跳法成功
                return 1;  // 成功返回 1
            }  // if 结束
            if (g[i][k] == -1) {  // 该跳法没有落点，无法继续
                return 0;  // 失败返回 0
            }  // if 结束
            if (f[i][k] != 0) {  // 已经计算过，直接复用结果
                return f[i][k];  // 返回记忆化结果
            }  // if 结束
            return f[i][k] = dfs(g[i][k], k ^ 1);  // 落点确定后换另一种跳法继续搜索（k ^ 1 在 0/1 间切换），结果存入 f
        };  // lambda 定义结束
        int ans = 0;  // ans 统计能跳到末尾的起点个数
        for (int i = 0; i < n; ++i) {  // 枚举每一个起点
            ans += dfs(i, 1);  // 从 i 出发且第一步是奇数跳，累加是否可行
        }  // for 循环结束
        return ans;  // 返回答案
    }  // 题解方法结束
};  // Solution 类结束
