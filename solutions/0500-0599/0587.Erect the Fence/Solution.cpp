// 题目：587. 安装栅栏（Erect the Fence）
// 思路：先按坐标字典序排序，用单调链（Andrew）扫描求凸包；第二趟放宽条件，把落在边界上的共线点也收进栅栏。
// 时间复杂度：O(n log n)，瓶颈在排序，两次扫描都是 O(n)；空间复杂度：O(n)，标记数组、栈与答案数组都至多 n 个元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> outerTrees(vector<vector<int>>& trees) {  // trees 是所有树的坐标；返回位于栅栏上的点
        int n = trees.size();  // 先记下点的个数，后面多处要用
        if (n < 4) return trees;  // 点数不足 4 个时所有点都在栅栏上，直接原样返回
        sort(trees.begin(), trees.end());  // 按 (x, y) 字典序排序，让扫描方向确定：先左后右、同列先下后上
        vector<int> vis(n);  // vis[i] 标记第 i 个点是否已经落在凸包边界上
        vector<int> stk(n + 10);  // 手工数组栈，存放点的下标；多开 10 个位置防止越界
        int cnt = 1;  // 栈内元素个数，先把排序后的第一个点（最左下）计入
        for (int i = 1; i < n; ++i) {  // 第一趟：从左到右求「下凸包」
            while (cnt > 1 && cross(trees[stk[cnt - 1]], trees[stk[cnt - 2]], trees[i]) < 0) vis[stk[--cnt]] = false;  // 栈顶造成右转说明它不是边界点：弹栈并撤销它的边界标记
            vis[i] = true;  // 当前点暂时视为边界点
            stk[cnt++] = i;  // 当前点入栈
        }
        int m = cnt;  // 记下下凸包结束时的栈大小，第二趟用它保护已确定的部分
        for (int i = n - 1; i >= 0; --i) {  // 第二趟：从右到左求「上凸包」，同时把被漏掉的共线点补收进来
            if (vis[i]) continue;  // 已经在下凸包上的点跳过，避免重复统计
            while (cnt > m && cross(trees[stk[cnt - 1]], trees[stk[cnt - 2]], trees[i]) < 0) --cnt;  // 同样右转就弹栈；条件 cnt > m 防止把下凸包的点弹掉
            stk[cnt++] = i;  // 当前点入栈
        }
        vector<vector<int>> ans;  // 保存栅栏上的所有点
        for (int i = 0; i < cnt - 1; ++i) ans.push_back(trees[stk[i]]);  // 栈的首尾是同一个点，所以少取最后一个避免重复
        return ans;  // 返回结果
    }

    int cross(vector<int>& a, vector<int>& b, vector<int>& c) {  // 求 a→b→c 的叉积（向量 ab 与 bc）
        return (b[0] - a[0]) * (c[1] - b[1]) - (b[1] - a[1]) * (c[0] - b[0]);  // 结果 < 0 表示右转（凹），= 0 表示三点共线
    }
};