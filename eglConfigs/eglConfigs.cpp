// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include EGL (for querying available configurations)
#include <EGL/egl.h>
#include <cstddef>

    
void print_egl_config(EGLDisplay eglDisplay, EGLConfig config) {
    int red_size, green_size, blue_size, alpha_size, depth_size;
    int stencil_size, sample_buffers, samples, buffer_size;
    
    eglGetConfigAttrib(eglDisplay, config, EGL_RED_SIZE, &red_size);
    eglGetConfigAttrib(eglDisplay, config, EGL_GREEN_SIZE, &green_size);
    eglGetConfigAttrib(eglDisplay, config, EGL_BLUE_SIZE, &blue_size);
    eglGetConfigAttrib(eglDisplay, config, EGL_ALPHA_SIZE, &alpha_size);
    eglGetConfigAttrib(eglDisplay, config, EGL_DEPTH_SIZE, &depth_size);
    eglGetConfigAttrib(eglDisplay, config, EGL_STENCIL_SIZE, &stencil_size);
    eglGetConfigAttrib(eglDisplay, config, EGL_SAMPLE_BUFFERS, &sample_buffers);
    eglGetConfigAttrib(eglDisplay, config, EGL_SAMPLES, &samples);
    eglGetConfigAttrib(eglDisplay, config, EGL_BUFFER_SIZE, &buffer_size);

    printf("EGL Configuration:\n");
    printf("  Red Size: %d\n", red_size);
    printf("  Green Size: %d\n", green_size);
    printf("  Blue Size: %d\n", blue_size);
    printf("  Alpha Size: %d\n", alpha_size);
    printf("  Depth Size: %d\n", depth_size);
    printf("  Stencil Size: %d\n", stencil_size);
    printf("  Sample Buffers: %d\n", sample_buffers);
    printf("  Samples: %d\n", samples);
    printf("  Buffer Size: %d\n", buffer_size);
}

int main(void)
{
    // Initialize EGL to query available configurations
    EGLDisplay eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (eglDisplay == EGL_NO_DISPLAY) {
        fprintf(stderr, "Failed to get EGL display\n");
        return -1;
    }

    if (!eglInitialize(eglDisplay, NULL, NULL)) {
        fprintf(stderr, "Failed to initialize EGL\n");
        return -1;
    }

    EGLint numConfigs;
    eglGetConfigs(eglDisplay, NULL, 0, &numConfigs);
    EGLConfig *configs = (EGLConfig *)malloc(numConfigs * sizeof(EGLConfig));
    eglGetConfigs(eglDisplay, configs, numConfigs, &numConfigs);

    printf("Available EGL configurations:\n");
    for (int i = 0; i < numConfigs; i++) {
        print_egl_config(eglDisplay, configs[i]);
        printf("\n");
    }

    free(configs);
    eglTerminate(eglDisplay);

    return 0;
}
