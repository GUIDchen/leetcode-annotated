// 题目：1564. 把箱子放进仓库里 I（Put Boxes Into the Warehouse I）
// 思路：箱子只能从仓库最左端推入，所以第 i 格实际可用的高度是左侧所有格子的前缀最小值；把箱子按边长升序，从仓库最右侧往前贪心匹配即可放最多箱子。
// 时间复杂度：O(n log n + m log m)，排序主导；空间复杂度：O(n)，前缀最小值数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxBoxesInWarehouse(vector<int>& boxes, vector<int>& warehouse) {  // boxes：每个箱子的边长；warehouse：仓库每格的高度
        int n = warehouse.size();  // n 为仓库格子数
        int left[n];  // left[i] 表示从最左端推到第 i 格时能通过的最大高度
        left[0] = warehouse[0];  // 第 0 格只受自身高度限制
        for (int i = 1; i < n; ++i) {  // 从左往右递推前缀最小值
            left[i] = min(left[i - 1], warehouse[i]);  // 前面的高度限制会一路传递下来，取二者较小值
        }  // 循环体结束
        sort(boxes.begin(), boxes.end());  // 箱子按边长升序排序，优先安排小箱子
        int i = 0, j = n - 1;  // i 指向下一个待放的箱子；j 指向从右往左的候选位置
        while (i < boxes.size()) {  // 只要还有箱子没尝试完就继续
            while (j >= 0 && left[j] < boxes[i]) {  // 从右往左找第一个能容纳当前箱子的位置
                --j;  // 该位置太矮，继续往左移
            }  // 内层循环结束
            if (j < 0) {  // 已经没有能容纳它的位置
                break;  // 后面的箱子只会更大，直接结束
            }  // if 结束
            ++i;  // 该箱子放好，处理下一个箱子
            --j;  // 该位置被占用，下一次从它左边继续找
        }  // 外层循环结束
        return i;  // i 恰好等于成功放入的箱子数
    }  // 方法结束
};  // 类定义结束