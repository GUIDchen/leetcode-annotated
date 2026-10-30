// 题目：858. 镜面反射（Mirror Reflection）
// 思路：把 p、q 同时除以最大公约数 g，之后只看 p/g 与 q/g 的奇偶性，就能确定激光最终命中的接收器编号。
// 时间复杂度：O(log min(p, q))，只求一次 gcd；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int mirrorReflection(int p, int q) {  // p：房间宽度；q：激光每走一个房间向上偏移的距离
        int g = __gcd(p, q);  // 求 p 与 q 的最大公约数，用来约去激光来回反射的重复周期
        p = (p / g) % 2;  // 约分后取 p/g 的奇偶性：奇数说明光线最终会到达房间右边界
        q = (q / g) % 2;  // 约分后取 q/g 的奇偶性：奇数说明光线最终会到达房间上边界
        if (p == 1 && q == 1) {  // 两个方向都到达边界时，激光落在 1 号接收器
            return 1;  // 返回 1 号接收器
        }  // if 分支结束
        return p == 1 ? 0 : 2;  // p/g 为奇数（q/g 为偶数）落在 0 号，否则落在 2 号
    }  // mirrorReflection 方法结束
};  // Solution 类定义结束