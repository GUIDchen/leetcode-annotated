// 4078. 连续三项斐波那契数之和（Three Fibonacci Sum）
// 核心思路：连续三项斐波那契数之和等于 2 * F(k+2)，故 n 可表示当且仅当 n 为偶数且 n / 2 是斐波那契数；先离线生成 1e9 以内的斐波那契集合，再 O(1) 查表。
// 复杂度：预处理 O(log n) 项斐波那契数，单次查询 O(1)，空间 O(log n)。
class Solution {  // 题解类
    static unordered_set<int> f;  // 静态集合，缓存 1e9 量级以内的斐波那契数（类内私有）

public:  // 对外接口
    bool threeFibonacciSum(int n) {  // 判断 n 能否表示为三个连续斐波那契数之和，即 n 为偶数且 n / 2 是斐波那契数
        return n % 2 == 0 && f.count(n / 2);  // 偶数是必要条件，再检查 n / 2 是否落在斐波那契集合中
    }  // 方法结束
};  // 类定义结束

unordered_set<int> Solution::f = [] {  // 用 lambda 在程序启动时就地完成斐波那契集合的预处理
    unordered_set<int> f;  // 待填充的集合
    int a = 0, b = 1;  // 相邻两项，F(0) = 0、F(1) = 1
    while (b < 1000000001) {  // 递推直到超过 1e9 + 1 的上界
        int c = a + b;  // 计算下一项
        a = b;  // 滚动前移
        b = c;  // 滚动前移
        f.insert(b);  // 把新生成的斐波那契数加入集合
    }  // 循环结束
    return f;  // 返回预处理结果
}();  // 立即执行上面的 lambda，完成静态成员初始化
