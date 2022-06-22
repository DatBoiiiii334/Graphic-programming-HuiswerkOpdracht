#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normals;
in vec4 FragPos;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;
uniform sampler2D texture_roughness1;
uniform sampler2D texture_ao1;

uniform vec3 cameraPosition;
uniform vec3 lightDirection;

float lerp(float a, float b, float t) {
    return a + (b - a) * t;
}

void main()
{
    vec3 lightDir = normalize(lightDirection);
    
    vec4 diffuse = texture(texture_diffuse1, TexCoords);
    vec4 specTex = texture(texture_specular1, TexCoords);

    //if (diffuse.r <= 0.5) {
    //    discard;
    //}

    float light = max(dot(-lightDir, Normals), 0.0);

    vec3 viewDir = normalize(cameraPosition - FragPos.rgb);
    vec3 refl = reflect(lightDir, Normals);

    float ambientOcclusion = texture(texture_ao1, TexCoords).r;
    
    float roughness = texture(texture_roughness1, TexCoords).r;
    float spec = pow(max(dot(viewDir, refl), 0.0), lerp(1, 256, roughness));
    vec3 specular = spec * specTex.rgb;

    vec4 result = diffuse * max(light * ambientOcclusion, 0.2 * ambientOcclusion) + vec4(specular, 0);
    //result.a = light;
    //result.a = diffuse.b /20;
    result.b = light * diffuse.b * 2;
    FragColor = result;
}