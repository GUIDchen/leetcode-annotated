// 3899. 三角形的内角度数 / Angles of a Triangle
// 核心思路：排序后先用两边之和大于第三边判定合法性，再用余弦定理求出两个角，第三个角由三角形内角和 180 度相减得到。
// 复杂度：时间 O(1)，空间 O(1)。
class Solution {  // 定义题解类
public:  // 公有接口
    vector<double> internalAngles(vector<int>& sides) {  // sides 为三边长，返回三个内角的度数；无法构成三角形时返回空数组
        sort(sides.begin(), sides.end());  // 排序后按 a <= b <= c 处理
        int a = sides[0], b = sides[1], c = sides[2];  // 取出三条边
        if (a + b <= c) {  // 两边之和不大于第三边，无法构成三角形
            return {};  // 返回空数组表示不合法
        }  // 合法性判断结束
        double A = acos((1.0 * b * b + 1.0 * c * c - 1.0 * a * a) / (2.0 * b * c)) * 180.0 / acos(-1.0);  // 余弦定理求角 A，再换算成角度
        double B = acos((1.0 * a * a + 1.0 * c * c - 1.0 * b * b) / (2.0 * a * c)) * 180.0 / acos(-1.0);  // 余弦定理求角 B，再换算成角度
        double C = 180.0 - A - B;  // 内角和 180 度，相减直接得到角 C
        return {A, B, C};  // 返回三个内角
    }  // internalAngles 结束
};  // 类定义结束