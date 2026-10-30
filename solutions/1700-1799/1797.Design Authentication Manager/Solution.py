# 题目：1797. 设计一个验证系统（Design Authentication Manager）
# 思路：用 defaultdict 保存「tokenId → 过期时间」；generate 写入 currentTime + timeToLive，renew 仅在未过期时刷新，countUnexpiredTokens 统计过期时间大于当前时间的个数。
# 时间复杂度：generate/renew 均摊 O(1)，统计为 O(n)；空间复杂度：O(n)。
class AuthenticationManager:  # 验证码管理器
    def __init__(self, timeToLive: int):  # 构造：timeToLive 是 token 的存活时长
        self.t = timeToLive  # 保存有效期
        self.d = defaultdict(int)  # tokenId → 过期时间；缺省值 0 便于 renew 里比较

    def generate(self, tokenId: str, currentTime: int) -> None:  # 生成或覆盖 token 的过期时间
        self.d[tokenId] = currentTime + self.t  # 过期时间 = 当前时间 + 有效期

    def renew(self, tokenId: str, currentTime: int) -> None:  # 续期
        if self.d[tokenId] <= currentTime:  # 未出现过（0）或已经过期，则不允许续期
            return  # 直接返回
        self.d[tokenId] = currentTime + self.t  # 未过期，刷新过期时间（等价于调用 generate）

    def countUnexpiredTokens(self, currentTime: int) -> int:  # 统计当前有效的 token 数
        return sum(exp > currentTime for exp in self.d.values())  # 对布尔值求和，结果就是有效 token 个数


# Your AuthenticationManager object will be instantiated and called as such:
# obj = AuthenticationManager(timeToLive)
# obj.generate(tokenId,currentTime)
# obj.renew(tokenId,currentTime)
# param_3 = obj.countUnexpiredTokens(currentTime)
