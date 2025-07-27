#version 120

// Outer Glow using attenuation

uniform sampler2D texture;
uniform vec4 innerColor;
uniform vec4 glowColor;
uniform float glowStrength;
uniform float glowRadius; // How far glow extends (in texels)
uniform vec2 texelSize; // vec2(1.0 / texWidth, 1.0 / texHeight)

void main()
{
    vec2 uv = gl_TexCoord[0].xy;
    vec4 center = texture2D(texture, uv);
    
// IF INNER PIXEL IS OPAQUE, APPLY INNER COLOR
    if (center.a > 0.0)
    {
        // APPLY TINT
        //vec3 tinted = mix(center.rgb, innerColor.rbg, innerColor.a);
        //gl_FragColor = vec4(tinted, center.a);

        gl_FragColor = innerColor;
        return;
    }

// ELSE, COMPUTE GLOW EFFECT
    float glow = 0.0;
    
    // Loop around current pixel in a square pattern
    for (float x = -glowRadius; x <= glowRadius; ++x) 
    {
        for (float y = -glowRadius; y <= glowRadius; ++y)
        {
            vec2 offset = vec2(x, y) * texelSize;
            vec4 sample = texture2D(texture, uv + offset);

            float distance = length(vec2(x, y)) / glowRadius;
            float attenuation = 1.0 / (1.0 + distance * distance * 5.0); // Quadratic falloff

            glow += sample.a * attenuation;
        }
    }

    // Normalize glow by area sampled
    float totalSamples = (2.0 * glowRadius + 1.0) * (2.0 * glowRadius + 1.0);
    glow /= totalSamples;

    // Final glow color
    vec4 finalColor = vec4(glowColor.rgb, glow * glowStrength * glowColor.a);
    gl_FragColor = finalColor;
}