// 题目：1580. 把箱子放进仓库里 II（Put Boxes Into the Warehouse II）
// 思路：每列真正可用的高度是 min(自身高度, max(左侧方向上限, 右侧方向上限))，因为箱子可以从更有利的一侧推进来；把列高与箱子都排序后，用双指针贪心依次塞入能装下的最矮列。
// 时间复杂度：O(n log n + m log m)，两边排序主导；空间复杂度：O(n)，需要 left、right 两个辅助数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxBoxesInWarehouse(vector<int>& boxes, vector<int>& warehouse) {  // boxes：箱子边长；warehouse：仓库每列的高度
        int n = warehouse.size();  // 仓库列数
        const int inf = 1 << 30;  // 足够大的哨兵值，表示「该方向没有更矮的列形成限制」
        vector<int> left(n, inf);  // left[i]：箱子从左侧推入到 i 时能通过的最大高度
        vector<int> right(n, inf);  // right[i]：箱子从右侧推入到 i 时能通过的最大高度
        for (int i = 1; i < n; ++i) {  // 从左往右预处理 left
            left[i] = min(left[i - 1], warehouse[i - 1]);  // i 的上限取「左侧方向上限」与「左边相邻列高」中的较小者（不含 i 自身）
        }  // 左预处理结束
        for (int i = n - 2; ~i; --i) {  // 从右往左预处理 right，~i 等价于 i >= 0
            right[i] = min(right[i + 1], warehouse[i + 1]);  // i 的上限取「右侧方向上限」与「右边相邻列高」中的较小者（不含 i 自身）
        }  // 右预处理结束
        for (int i = 0; i < n; ++i) {  // 把每列高度改成它能真正容纳的最大箱子边长
            warehouse[i] = min(warehouse[i], max(left[i], right[i]));  // 箱子可任选更有利的一侧推入，因此取左右两个方向上限的较大者
        }  // 预处理结束
        sort(boxes.begin(), boxes.end());  // 箱子按边长升序排序，便于贪心
        sort(warehouse.begin(), warehouse.end());  // 仓库列按可用高度升序排序
        int ans = 0;  // 已放入的箱子数
        int i = 0;  // 指向当前可用的最矮仓库列
        for (int x : boxes) {  // 从小到大依次尝试每个箱子
            while (i < n && warehouse[i] < x) {  // 跳过装不下当前箱子的仓库列
                ++i;  // 换下一列
            }  // 跳过循环结束
            if (i == n) {  // 所有列都已用完
                break;  // 后面的箱子只会更大，直接结束
            }  // if 分支结束
            ++ans;  // 当前箱子可以放入，计数加一
            ++i;  // 该列被占用，指针后移
        }  // for 循环结束
        return ans;  // 返回最多能放下的箱子数
    }  // 方法结束
};  // 题解类结束