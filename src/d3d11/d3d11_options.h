#pragma once

#include "../util/config/config.h"

#include "../dxgi/dxgi_options.h"

#include "../dxvk/dxvk_device.h"

#include "d3d11_include.h"

namespace dxvk {
  
  struct D3D11Options {
    D3D11Options(const Config& config, const Rc<DxvkDevice>& device);

    /// Enables speed hack for mapping on deferred contexts
    ///
    /// This can substantially speed up some games, but may
    /// cause issues if the game submits command lists more
    /// than once.
    bool dcSingleUseMode;

    /// Enables sm4-compliant division-by-zero behaviour
    /// Windows drivers don't normally do this, but some
    /// games may expect correct behaviour.
    bool strictDivision;

    /// Enables out-of-bounds access check for constant
    /// buffers. Workaround for a few broken games that
    /// access random data inside their shaders.
    bool constantBufferRangeCheck;

    /// Zero-initialize workgroup memory
    ///
    /// Workargound for games that don't initialize
    /// TGSM in compute shaders before reading it.
    bool zeroInitWorkgroupMemory;

    /// Use relaxed memory barriers
    ///
    /// May improve performance in some games,
    /// but might also cause rendering issues.
    bool relaxedBarriers;

    /// Maximum tessellation factor.
    ///
    /// Limits tessellation factors in tessellation
    /// control shaders. Values from 8 to 64 are
    /// supported, other values will be ignored.
    int32_t maxTessFactor;

    /// Anisotropic filter override
    ///
    /// Enforces anisotropic filtering with the
    /// given anisotropy value for all samplers.
    int32_t samplerAnisotropy;
    
    /// Back buffer count for the Vulkan swap chain.
    /// Overrides DXGI_SWAP_CHAIN_DESC::BufferCount.
    int32_t numBackBuffers;

    /// Sync interval. Overrides the value
    /// passed to IDXGISwapChain::Present.
    int32_t syncInterval;

    /// Override maximum frame latency if the app specifies
    /// a higher value. May help with frame timing issues.
    int32_t maxFrameLatency;

    /// Defer surface creation until first present call. This
    /// fixes issues with games that create multiple swap chains
    /// for a single window that may interfere with each other.
    bool deferSurfaceCreation;

    /// Apitrace mode: Maps all buffers in cached memory.
    /// Enabled automatically if dxgitrace.dll is attached.
    bool apitraceMode;
  };
  
}