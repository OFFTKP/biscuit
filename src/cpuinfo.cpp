// Copyright (c), 2022, KNS Group LLC (YADRO)
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <atomic>
#include <biscuit/assert.hpp>
#include <biscuit/cpuinfo.hpp>
#include <csignal>
#include <vector>

#if defined(__linux__) && defined(__riscv)
#include <asm/hwcap.h>
#include <sys/auxv.h>
#include <sys/prctl.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <utility>

#ifdef SYS_riscv_hwprobe
#include <asm/hwprobe.h>
#endif
#endif

#ifndef RISCV_HWPROBE_BASE_BEHAVIOR_IMA
#define RISCV_HWPROBE_BASE_BEHAVIOR_IMA (1ULL << 0)
#endif

#ifndef RISCV_HWPROBE_IMA_FD
#define RISCV_HWPROBE_IMA_FD            (1ULL << 0)
#endif

#ifndef RISCV_HWPROBE_IMA_C
#define RISCV_HWPROBE_IMA_C             (1ULL << 1)
#endif

#ifndef RISCV_HWPROBE_IMA_V
#define RISCV_HWPROBE_IMA_V             (1ULL << 2)
#endif

#ifndef RISCV_HWPROBE_EXT_ZBA
#define RISCV_HWPROBE_EXT_ZBA           (1ULL << 3)
#endif

#ifndef RISCV_HWPROBE_EXT_ZBB
#define RISCV_HWPROBE_EXT_ZBB           (1ULL << 4)
#endif

#ifndef RISCV_HWPROBE_EXT_ZBS
#define RISCV_HWPROBE_EXT_ZBS           (1ULL << 5)
#endif

#ifndef RISCV_HWPROBE_EXT_ZICBOZ
#define RISCV_HWPROBE_EXT_ZICBOZ        (1ULL << 6)
#endif

#ifndef RISCV_HWPROBE_EXT_ZBC
#define RISCV_HWPROBE_EXT_ZBC           (1ULL << 7)
#endif

#ifndef RISCV_HWPROBE_EXT_ZBKB
#define RISCV_HWPROBE_EXT_ZBKB          (1ULL << 8)
#endif

#ifndef RISCV_HWPROBE_EXT_ZBKC
#define RISCV_HWPROBE_EXT_ZBKC          (1ULL << 9)
#endif

#ifndef RISCV_HWPROBE_EXT_ZBKX
#define RISCV_HWPROBE_EXT_ZBKX          (1ULL << 10)
#endif

#ifndef RISCV_HWPROBE_EXT_ZKND
#define RISCV_HWPROBE_EXT_ZKND          (1ULL << 11)
#endif

#ifndef RISCV_HWPROBE_EXT_ZKNE
#define RISCV_HWPROBE_EXT_ZKNE          (1ULL << 12)
#endif

#ifndef RISCV_HWPROBE_EXT_ZKNH
#define RISCV_HWPROBE_EXT_ZKNH          (1ULL << 13)
#endif

#ifndef RISCV_HWPROBE_EXT_ZKSED
#define RISCV_HWPROBE_EXT_ZKSED         (1ULL << 14)
#endif

#ifndef RISCV_HWPROBE_EXT_ZKSH
#define RISCV_HWPROBE_EXT_ZKSH          (1ULL << 15)
#endif

#ifndef RISCV_HWPROBE_EXT_ZKT
#define RISCV_HWPROBE_EXT_ZKT           (1ULL << 16)
#endif

#ifndef RISCV_HWPROBE_EXT_ZVBB
#define RISCV_HWPROBE_EXT_ZVBB          (1ULL << 17)
#endif

#ifndef RISCV_HWPROBE_EXT_ZVBC
#define RISCV_HWPROBE_EXT_ZVBC          (1ULL << 18)
#endif

#ifndef RISCV_HWPROBE_EXT_ZVKB
#define RISCV_HWPROBE_EXT_ZVKB          (1ULL << 19)
#endif

#ifndef RISCV_HWPROBE_EXT_ZVKG
#define RISCV_HWPROBE_EXT_ZVKG          (1ULL << 20)
#endif

#ifndef RISCV_HWPROBE_EXT_ZVKNED
#define RISCV_HWPROBE_EXT_ZVKNED        (1ULL << 21)
#endif

#ifndef RISCV_HWPROBE_EXT_ZVKNHA
#define RISCV_HWPROBE_EXT_ZVKNHA        (1ULL << 22)
#endif

#ifndef RISCV_HWPROBE_EXT_ZVKNHB
#define RISCV_HWPROBE_EXT_ZVKNHB        (1ULL << 23)
#endif

#ifndef RISCV_HWPROBE_EXT_ZVKSED
#define RISCV_HWPROBE_EXT_ZVKSED        (1ULL << 24)
#endif

#ifndef RISCV_HWPROBE_EXT_ZVKSH
#define RISCV_HWPROBE_EXT_ZVKSH         (1ULL << 25)
#endif

#ifndef RISCV_HWPROBE_EXT_ZVKT
#define RISCV_HWPROBE_EXT_ZVKT          (1ULL << 26)
#endif

#ifndef RISCV_HWPROBE_EXT_ZFH
#define RISCV_HWPROBE_EXT_ZFH           (1ULL << 27)
#endif

#ifndef RISCV_HWPROBE_EXT_ZFHMIN
#define RISCV_HWPROBE_EXT_ZFHMIN        (1ULL << 28)
#endif

#ifndef RISCV_HWPROBE_EXT_ZIHINTNTL
#define RISCV_HWPROBE_EXT_ZIHINTNTL     (1ULL << 29)
#endif

#ifndef RISCV_HWPROBE_EXT_ZVFH
#define RISCV_HWPROBE_EXT_ZVFH          (1ULL << 30)
#endif

#ifndef RISCV_HWPROBE_EXT_ZVFHMIN
#define RISCV_HWPROBE_EXT_ZVFHMIN       (1ULL << 31)
#endif

#ifndef RISCV_HWPROBE_EXT_ZFA
#define RISCV_HWPROBE_EXT_ZFA           (1ULL << 32)
#endif

#ifndef RISCV_HWPROBE_EXT_ZTSO
#define RISCV_HWPROBE_EXT_ZTSO          (1ULL << 33)
#endif

#ifndef RISCV_HWPROBE_EXT_ZACAS
#define RISCV_HWPROBE_EXT_ZACAS         (1ULL << 34)
#endif

#ifndef RISCV_HWPROBE_EXT_ZICOND
#define RISCV_HWPROBE_EXT_ZICOND        (1ULL << 35)
#endif

#ifndef RISCV_HWPROBE_EXT_ZIHINTPAUSE
#define RISCV_HWPROBE_EXT_ZIHINTPAUSE   (1ULL << 36)
#endif

#ifndef RISCV_HWPROBE_EXT_ZVE32X
#define RISCV_HWPROBE_EXT_ZVE32X        (1ULL << 37)
#endif

#ifndef RISCV_HWPROBE_EXT_ZVE32F
#define RISCV_HWPROBE_EXT_ZVE32F        (1ULL << 38)
#endif

#ifndef RISCV_HWPROBE_EXT_ZVE64X
#define RISCV_HWPROBE_EXT_ZVE64X        (1ULL << 39)
#endif

#ifndef RISCV_HWPROBE_EXT_ZVE64F
#define RISCV_HWPROBE_EXT_ZVE64F        (1ULL << 40)
#endif

#ifndef RISCV_HWPROBE_EXT_ZVE64D
#define RISCV_HWPROBE_EXT_ZVE64D        (1ULL << 41)
#endif

#ifndef RISCV_HWPROBE_EXT_ZIMOP
#define RISCV_HWPROBE_EXT_ZIMOP         (1ULL << 42)
#endif

#ifndef RISCV_HWPROBE_EXT_ZCA
#define RISCV_HWPROBE_EXT_ZCA           (1ULL << 43)
#endif

#ifndef RISCV_HWPROBE_EXT_ZCB
#define RISCV_HWPROBE_EXT_ZCB           (1ULL << 44)
#endif

#ifndef RISCV_HWPROBE_EXT_ZCD
#define RISCV_HWPROBE_EXT_ZCD           (1ULL << 45)
#endif

#ifndef RISCV_HWPROBE_EXT_ZCF
#define RISCV_HWPROBE_EXT_ZCF           (1ULL << 46)
#endif

#ifndef RISCV_HWPROBE_EXT_ZCMOP
#define RISCV_HWPROBE_EXT_ZCMOP         (1ULL << 47)
#endif

#ifndef RISCV_HWPROBE_EXT_ZAWRS
#define RISCV_HWPROBE_EXT_ZAWRS         (1ULL << 48)
#endif

#ifndef COMPAT_HWCAP_ISA_I
#define COMPAT_HWCAP_ISA_I  (1U << ('I' - 'A'))
#endif

#ifndef COMPAT_HWCAP_ISA_M
#define COMPAT_HWCAP_ISA_M  (1U << ('M' - 'A'))
#endif

#ifndef COMPAT_HWCAP_ISA_A
#define COMPAT_HWCAP_ISA_A  (1U << ('A' - 'A'))
#endif

#ifndef COMPAT_HWCAP_ISA_F
#define COMPAT_HWCAP_ISA_F  (1U << ('F' - 'A'))
#endif

#ifndef COMPAT_HWCAP_ISA_D
#define COMPAT_HWCAP_ISA_D  (1U << ('D' - 'A'))
#endif

#ifndef COMPAT_HWCAP_ISA_C
#define COMPAT_HWCAP_ISA_C  (1U << ('C' - 'A'))
#endif

#ifndef COMPAT_HWCAP_ISA_V
#define COMPAT_HWCAP_ISA_V  (1U << ('V' - 'A'))
#endif

namespace biscuit {
void EmitInstructionFromExtension(Assembler& as, RISCVExtension extension) {
    switch (extension) {
        case RISCVExtension::I: {
            as.ADD(t0, t0, t0);
            break;
        }
        case RISCVExtension::M: {
            as.MUL(t0, t0, t0);
            break;
        }
        case RISCVExtension::A: {
            as.AMOADD_D(Ordering::AQRL, t0, t0, s2);
            break;
        }
        case RISCVExtension::F: {
            as.FADD_S(ft0, ft0, ft0);
            break;
        }
        case RISCVExtension::D: {
            as.FADD_D(ft0, ft0, ft0);
            break;
        }
        case RISCVExtension::C:
        case RISCVExtension::Zca: {
            as.C_ADD(t0, t0);
            break;
        }
        case RISCVExtension::V: {
            as.VAND(v1, v1, v1);
            break;
        }
        case RISCVExtension::Zba: {
            as.SH1ADD(t0, t0, t0);
            break;
        }
        case RISCVExtension::Zbkb: {
            as.PACK(t0, t0, t0);
            break;
        }
        case RISCVExtension::Zbb: {
            as.ZEXTH(t0, t0);
            break;
        }
        case RISCVExtension::Zbs: {
            as.BEXT(t0, t0, t0);
            break;
        }
        case RISCVExtension::Zicboz: {
            as.CBO_ZERO(s2);
            break;
        }
        case RISCVExtension::Zbkc: {
            as.CLMUL(t0, t0, t0);
            break;
        }
        case RISCVExtension::Zbc: {
            as.CLMULR(t0, t0, t0);
            break;
        }
        case RISCVExtension::Zbkx: {
            as.XPERM4(t0, t0, t0);
            break;
        }
        case RISCVExtension::Zknd: {
            as.AES64DS(t0, t0, t0);
            break;
        }
        case RISCVExtension::Zkne: {
            as.AES64ES(t0, t0, t0);
            break;
        }
        case RISCVExtension::Zknh: {
            as.SHA256SIG0(t0, t0);
            break;
        }
        case RISCVExtension::Zksed: {
            as.SM4ED(t0, t0, t0, 0);
            break;
        }
        case RISCVExtension::Zksh: {
            as.SM3P0(t0, t0);
            break;
        }
        case RISCVExtension::Zcf: {
            as.C_FLW(f0, 0, s2);
            break;
        }
        case RISCVExtension::Zcd: {
            as.C_FLD(f0, 0, s2);
            break;
        }
        case RISCVExtension::Zcb: {
            as.C_NOT(t0);
            break;
        }
        case RISCVExtension::Zacas: {
            as.AMOCAS_D(Ordering::AQRL, t0, t0, s2);
            break;
        }
        case RISCVExtension::Zicond: {
            as.CZERO_EQZ(t0, t0, t0);
            break;
        }
        case RISCVExtension::Zvkb: {
            as.VANDN(v1, v1, v1);
            break;
        }
        case RISCVExtension::Zvbb: {
            as.VCTZ(v1, v1);
            break;
        }
        case RISCVExtension::Zvfhmin: {
            as.VSETIVLI(x0, 1, SEW::E16);
            as.VFWCVT_F_F(v1, v1);
            break;
        }
        case RISCVExtension::Zvfh: {
            as.VSETIVLI(x0, 1, SEW::E16);
            as.VFADD(v1, v1, v1);
            break;
        }
        case RISCVExtension::Zvkg: {
            as.VSETIVLI(x0, 4, SEW::E32);
            as.VGHSH(v1, v1, v1);
            break;
        }
        case RISCVExtension::Zvkned: {
            as.VSETIVLI(x0, 4, SEW::E32);
            as.VAESEF_VV(v1, v1);
            break;
        }
        case RISCVExtension::Zvknha: {
            as.VSETIVLI(x0, 4, SEW::E32);
            as.VSHA2MS(v1, v1, v1);
            break;
        }
        case RISCVExtension::Zvknhb: {
            as.VSETIVLI(x0, 4, SEW::E64);
            as.VSHA2MS(v1, v1, v1);
            break;
        }
        case RISCVExtension::Zvbc: {
            as.VSETIVLI(x0, 1, SEW::E64);
            as.VCLMUL(v1, v1, v1);
            break;
        }
        case RISCVExtension::Zvksed: {
            as.VSETIVLI(x0, 4, SEW::E32);
            as.VSM4R_VV(v1, v1);
            break;
        }
        case RISCVExtension::Zvksh: {
            as.VSETIVLI(x0, 8, SEW::E32);
            as.VSM3ME(v1, v1, v1);
            break;
        }
        case RISCVExtension::Zfhmin: {
            as.FMV_X_H(t0, f0);
            break;
        }
        case RISCVExtension::Zfh: {
            as.FADD_H(f0, f0, f0);
            break;
        }
        case RISCVExtension::Zfa: {
            as.FLI_S(f0, 0);
            break;
        }
        case RISCVExtension::Zihintpause:
        case RISCVExtension::Zihintntl:
        case RISCVExtension::Zawrs:
        case RISCVExtension::Zcmop:
        case RISCVExtension::Zimop:
        case RISCVExtension::Zkt:
        case RISCVExtension::Zvkt: 
        case RISCVExtension::Ztso:
        case RISCVExtension::Zve32x:
        case RISCVExtension::Zve32f:
        case RISCVExtension::Zve64f:
        case RISCVExtension::Zve64d:
        case RISCVExtension::Zve64x: {
            // Can't be checked this way
            as.LI(s0, 0);
            break;
        }
        case RISCVExtension::Count: {
            BISCUIT_ASSERT(false);
            break;
        }
    }
}

bool FeatureCheckFallback(RISCVExtension extension) {
    static std::vector<uint8_t> features(static_cast<size_t>(RISCVExtension::Count));
    static std::atomic_flag initialized = ATOMIC_FLAG_INIT;

    if (!initialized.test_and_set()) { // make sure multiple threads don't initialize at the same time
        biscuit::Assembler as;

        // The signal handler sets s0 to 0 (false) to indicate
        // that the extension is not available.
        const auto signalHandler = reinterpret_cast<void(*)(int)>(as.GetCursorPointer());
        as.LI(s0, 0); this s0 stuff isnt gonna work, use a proper signal handler and userdata
        as.RET();

        const auto entrypoint = reinterpret_cast<void(*)()>(as.GetCursorPointer());
        as.LI(s1, (uint64_t)features.data());

        // Set s2 to a valid address for instructions that need to read from memory
        static uint64_t dummy = 0;
        as.LI(s2, (uint64_t)&dummy);

        for (int i = 0; i < static_cast<int>(RISCVExtension::Count); i++) {
            as.LI(s0, 1); // Assume extension exists
            EmitInstructionFromExtension(as, extension);
            as.SB(s0, i, s1); // if signal handler was hit, s0 will be 0
        }
        as.RET();

        signal(SIGILL, signalHandler);

        as.GetCodeBuffer().SetExecutable();
        entrypoint();

        signal(SIGILL, SIG_DFL);
    }

    return features[static_cast<size_t>(extension)] != 0;
}

bool CPUInfo::Has(RISCVExtension extension) const {
#if defined(__linux__) && defined(__riscv)
#ifdef SYS_riscv_hwprobe
    static const auto [result, ima, features0] = []() {
        riscv_hwprobe pairs[] = {
            {RISCV_HWPROBE_KEY_BASE_BEHAVIOR, 0},
            {RISCV_HWPROBE_KEY_IMA_EXT_0, 0},
        };

        long result = syscall(SYS_riscv_hwprobe, pairs, std::size(pairs), 0, nullptr, 0);
        uint64_t ima = pairs[0].value;
        uint64_t features0 = pairs[1].value;
        
        return std::make_tuple(result, ima, features0);
    }();

    // Older kernel versions don't support this syscall
    // Fallback to signal handler method
    if (result < 0) {
        return FeatureCheckFallback(extension);
    }

    switch (extension) {
        case RISCVExtension::I:
        case RISCVExtension::M:
        case RISCVExtension::A: {
            return ima == RISCV_HWPROBE_BASE_BEHAVIOR_IMA;
        }
        case RISCVExtension::F:
        case RISCVExtension::D:
            return (features0 & RISCV_HWPROBE_IMA_FD) != 0;
        case RISCVExtension::C:
            return (features0 & RISCV_HWPROBE_IMA_C) != 0;
        case RISCVExtension::V:
            return (features0 & RISCV_HWPROBE_IMA_V) != 0;
        case RISCVExtension::Zba:
            return (features0 & RISCV_HWPROBE_EXT_ZBA) != 0;
        case RISCVExtension::Zbb:
            return (features0 & RISCV_HWPROBE_EXT_ZBB) != 0;
        case RISCVExtension::Zbs:
            return (features0 & RISCV_HWPROBE_EXT_ZBS) != 0;
        case RISCVExtension::Zicboz:
            return (features0 & RISCV_HWPROBE_EXT_ZICBOZ) != 0;
        case RISCVExtension::Zbc:
            return (features0 & RISCV_HWPROBE_EXT_ZBC) != 0;
        case RISCVExtension::Zbkb:
            return (features0 & RISCV_HWPROBE_EXT_ZBKB) != 0;
        case RISCVExtension::Zbkc:
            return (features0 & RISCV_HWPROBE_EXT_ZBKC) != 0;
        case RISCVExtension::Zbkx:
            return (features0 & RISCV_HWPROBE_EXT_ZBKX) != 0;
        case RISCVExtension::Zknd:
            return (features0 & RISCV_HWPROBE_EXT_ZKND) != 0;
        case RISCVExtension::Zkne:
            return (features0 & RISCV_HWPROBE_EXT_ZKNE) != 0;
        case RISCVExtension::Zknh:
            return (features0 & RISCV_HWPROBE_EXT_ZKNH) != 0;
        case RISCVExtension::Zksed:
            return (features0 & RISCV_HWPROBE_EXT_ZKSED) != 0;
        case RISCVExtension::Zksh:
            return (features0 & RISCV_HWPROBE_EXT_ZKSH) != 0;
        case RISCVExtension::Zkt:
            return (features0 & RISCV_HWPROBE_EXT_ZKT) != 0;
        case RISCVExtension::Zvbb:
            return (features0 & RISCV_HWPROBE_EXT_ZVBB) != 0;
        case RISCVExtension::Zvbc:
            return (features0 & RISCV_HWPROBE_EXT_ZVBC) != 0;
        case RISCVExtension::Zvkb:
            return (features0 & RISCV_HWPROBE_EXT_ZVKB) != 0;
        case RISCVExtension::Zvkg:
            return (features0 & RISCV_HWPROBE_EXT_ZVKG) != 0;
        case RISCVExtension::Zvkned:
            return (features0 & RISCV_HWPROBE_EXT_ZVKNED) != 0;
        case RISCVExtension::Zvknha:
            return (features0 & RISCV_HWPROBE_EXT_ZVKNHA) != 0;
        case RISCVExtension::Zvknhb:
            return (features0 & RISCV_HWPROBE_EXT_ZVKNHB) != 0;
        case RISCVExtension::Zvksed:
            return (features0 & RISCV_HWPROBE_EXT_ZVKSED) != 0;
        case RISCVExtension::Zvksh:
            return (features0 & RISCV_HWPROBE_EXT_ZVKSH) != 0;
        case RISCVExtension::Zvkt:
            return (features0 & RISCV_HWPROBE_EXT_ZVKT) != 0;
        case RISCVExtension::Zfh:
            return (features0 & RISCV_HWPROBE_EXT_ZFH) != 0;
        case RISCVExtension::Zfhmin:
            return (features0 & RISCV_HWPROBE_EXT_ZFHMIN) != 0;
        case RISCVExtension::Zihintntl:
            return (features0 & RISCV_HWPROBE_EXT_ZIHINTNTL) != 0;
        case RISCVExtension::Zvfh:
            return (features0 & RISCV_HWPROBE_EXT_ZVFH) != 0;
        case RISCVExtension::Zvfhmin:
            return (features0 & RISCV_HWPROBE_EXT_ZVFHMIN) != 0;
        case RISCVExtension::Zfa:
            return (features0 & RISCV_HWPROBE_EXT_ZFA) != 0;
        case RISCVExtension::Ztso:
            return (features0 & RISCV_HWPROBE_EXT_ZTSO) != 0;
        case RISCVExtension::Zacas:
            return (features0 & RISCV_HWPROBE_EXT_ZACAS) != 0;
        case RISCVExtension::Zicond:
            return (features0 & RISCV_HWPROBE_EXT_ZICOND) != 0;
        case RISCVExtension::Zihintpause:
            return (features0 & RISCV_HWPROBE_EXT_ZIHINTPAUSE) != 0;
        case RISCVExtension::Zve32f:
            return (features0 & RISCV_HWPROBE_EXT_ZVE32F) != 0;
        case RISCVExtension::Zve32x:
            return (features0 & RISCV_HWPROBE_EXT_ZVE32X) != 0;
        case RISCVExtension::Zve64d:
            return (features0 & RISCV_HWPROBE_EXT_ZVE64D) != 0;
        case RISCVExtension::Zve64f:
            return (features0 & RISCV_HWPROBE_EXT_ZVE64F) != 0;
        case RISCVExtension::Zve64x:
            return (features0 & RISCV_HWPROBE_EXT_ZVE64X) != 0;
        case RISCVExtension::Zimop:
            return (features0 & RISCV_HWPROBE_EXT_ZIMOP) != 0;
        case RISCVExtension::Zca:
            return (features0 & RISCV_HWPROBE_EXT_ZCA) != 0;
        case RISCVExtension::Zcb:
            return (features0 & RISCV_HWPROBE_EXT_ZCB) != 0;
        case RISCVExtension::Zcd:
            return (features0 & RISCV_HWPROBE_EXT_ZCD) != 0;
        case RISCVExtension::Zcf:
            return (features0 & RISCV_HWPROBE_EXT_ZCF) != 0;
        case RISCVExtension::Zcmop:
            return (features0 & RISCV_HWPROBE_EXT_ZCMOP) != 0;
        case RISCVExtension::Zawrs:
            return (features0 & RISCV_HWPROBE_EXT_ZAWRS) != 0;
        case RISCVExtension::Count:
            BISCUIT_ASSERT(false);
            return false;
    }
#else
    return FeatureCheckFallback(extension);
#endif
#else
    (void)extension;
    return false;
#endif
}

uint32_t CPUInfo::GetVlenb() const {
    if(Has(RISCVExtension::V)) {
        static CSRReader<CSR::VLenb> csrReader;
        const static auto getVLEN = csrReader.GetCode<uint32_t (*)()>();
        return getVLEN();
    }

    return 0;
}

} // namespace biscuit
