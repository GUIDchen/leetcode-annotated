// 题目：341. 扁平化嵌套列表迭代器（Flatten Nested List Iterator）
// 核心思路：构造时用 DFS 把嵌套结构一次性展平成一维数组，next/hasNext 只需按数组下标顺序返回。
// 时间复杂度：构造 O(N) 展平全部元素，next/hasNext 均摊 O(1)；空间复杂度：O(N)，用一个数组保存所有整数。
/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */

class NestedIterator {  // 迭代器类：先把嵌套列表展平成数组，再按下标逐个取出
public:  // 以下构造函数与对外方法公开
    NestedIterator(vector<NestedInteger>& nestedList) {  // 构造函数：把传入的嵌套列表一次性展平到 nums
        auto dfs = [&](this auto&& dfs, vector<NestedInteger>& ls) -> void {  // C++23 显式对象参数 this auto&& dfs，让 lambda 能递归调用自身
            for (auto& x : ls) {  // 遍历当前层的每个元素
                if (x.isInteger()) {  // 元素是单个整数
                    nums.push_back(x.getInteger());  // 按顺序追加到结果数组
                } else {  // 元素是子列表
                    dfs(x.getList());  // 递归展平子列表
                }  // if/else 分支结束
            }  // for 循环结束
        };  // lambda 定义结束
        dfs(nestedList);  // 从根层嵌套列表开始展平
    }  // 构造函数结束

    int next() {  // 返回下一个整数
        return nums[++i];  // 先自增下标再取值，i 初始为 -1 正好指向第 0 个元素
    }  // next 方法结束

    bool hasNext() {  // 判断是否还有下一个整数
        return i + 1 < nums.size();  // 下标 i+1 仍未越界就说明还有元素
    }  // hasNext 方法结束

private:  // 以下为实现细节，不对外暴露
    vector<int> nums;  // 展平后得到的一维整数数组
    int i = -1;  // 当前已经返回元素的下标，从 -1 开始
};  // 类定义结束

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */
