// 题目：768. 最多能完成排序的块 II（Max Chunks To Make Sorted II）
// 核心思路：用单调不减栈保存每个块的最大值，遇到比栈顶小的值就向前合并所有受影响的块。
// 时间复杂度 O(n)（每个下标最多进出栈各一次）；空间复杂度 O(n)（栈最多保存 n 个块的最大值）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对判题器可见
    int maxChunksToSorted(vector<int>& arr) {  // arr：允许重复元素的输入数组；返回最多能切分成多少块
        stack<int> stk;  // 单调不减栈：每个元素代表「当前某个块内的最大值」，自底向上不递减
        for (int& v : arr) {  // 从左到右扫描，v 是当前元素（引用绑定，避免拷贝）
            if (stk.empty() || stk.top() <= v)  // 栈空（第一个元素）或当前值不小于栈顶：它不会和已有块冲突
                stk.push(v);  // 直接压栈，作为新块的最大值
            else {  // 否则 v 比栈顶小：v 必须并入前面的块，触发连续合并
                int mx = stk.top();  // 记下当前栈顶 mx，它代表这个被合并块的最大值，最后要写回
                stk.pop();  // 先弹出这个块的标记，准备继续向前比较
                while (!stk.empty() && stk.top() > v) stk.pop();  // 把所有最大值仍大于 v 的块一起弹出，它们只能并成同一个块
                stk.push(mx);  // 把合并后大块的最大值 mx 压回栈中
            }  // else 分支结束
        }  // for 循环结束
        return stk.size();  // 栈中剩下的每个元素对应一个块，数量即答案
    }  // 方法结束
};  // 类定义结束