# 3606. 优惠券校验器 / Coupon Code Validator
# 核心思路：先挑出同时满足“状态有效、业务类别合法、券码只含字母/数字/下划线”的下标，再按业务类别、券码双关键字升序排序后输出券码。
# 复杂度：时间 O(n log n)（排序主导），空间 O(n)，n 为优惠券数量。
class Solution:  # 定义题解类
    def validateCoupons(  # 主函数：入参为券码、业务类别、是否有效三个平行列表
        self, code: List[str], businessLine: List[str], isActive: List[bool]  # 后两个入参：业务类别列表与有效状态列表
    ) -> List[str]:  # 返回按规则排序后的合法券码列表
        def check(s: str) -> bool:  # 内部辅助函数：判断券码是否只含字母、数字、下划线
            if not s:  # 空串不算合法券码
                return False  # 直接判定为不合法
            for c in s:  # 逐字符检查
                if not (c.isalpha() or c.isdigit() or c == "_"):  # 出现非字母、非数字、非下划线的字符即非法
                    return False  # 返回不合法
            return True  # 全部字符检查通过，返回合法

        idx = []  # 记录通过校验的券码下标
        bs = {"electronics", "grocery", "pharmacy", "restaurant"}  # 四种合法的业务类别
        for i, (c, b, a) in enumerate(zip(code, businessLine, isActive)):  # 把三个平行列表按位置打包后逐个枚举
            if a and b in bs and check(c):  # 状态有效、类别合法、券码字符合法三者同时成立
                idx.append(i)  # 保存该券的下标
        idx.sort(key=lambda i: (businessLine[i], code[i]))  # 按业务类别、券码双关键字升序排序
        return [code[i] for i in idx]  # 按下标取出券码，组成最终答案
