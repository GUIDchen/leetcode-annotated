// 题目：264. 丑数 II（Ugly Number II）
// 思路：小根堆始终放着候选丑数，每弹出一个最小丑数，就把它乘 2/3/5 得到的新丑数（去重后）入堆，弹到第 n 次即为答案。
// 时间复杂度：O(n log n)，每次弹堆加三次入堆；空间复杂度：O(n)，堆与去重集合最多存 O(n) 个数。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解法接口
    int nthUglyNumber(int n) {  // n 表示要求的第几个丑数，返回第 n 个丑数
        priority_queue<long, vector<long>, greater<long>> q;  // 小根堆，保证每次取出当前最小的候选丑数；元素用 long 防溢出
        q.push(1l);  // 1 是最小的丑数，先入堆
        unordered_set<long> vis{{1l}};  // 哈希集合记录已入过堆的丑数，避免同一个数重复入堆
        long ans = 1;  // ans 暂存每次弹出的丑数，循环结束后就是第 n 个
        vector<int> f = {2, 3, 5};  // 丑数只能由 2、3、5 这三个因子生成
        while (n--) {  // 循环 n 次，第 n 次弹出的就是第 n 个丑数
            ans = q.top();  // 取出堆顶，即当前最小的丑数
            q.pop();  // 弹出，表示这个丑数已经被消耗掉
            for (int& v : f) {  // 用当前丑数分别乘 2、3、5 生成后面的丑数
                long nxt = ans * v;  // 乘积可能超出 int，先用 long 暂存
                if (!vis.count(nxt)) {  // 只把没出现过的丑数入堆，保证弹出序列严格递增不重复
                    vis.insert(nxt);  // 标记该丑数已经出现过
                    q.push(nxt);  // 放进小根堆参与后续排序
                }  // 去重判断结束
            }  // 三种因子的生成循环结束
        }  // n 次弹出结束
        return (int) ans;  // 转回 int 返回，题目保证答案在 int 范围内
    }  // 方法结束
};  // 类定义结束