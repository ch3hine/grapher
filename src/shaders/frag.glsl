#version 330 core

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform sampler2D texture_diffuse1;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform bool useTexture;

struct DirectionalLight {
    vec3 direction;
    vec3 color;
};

struct PointLight {
    vec3 position;
    vec3 color;
};

uniform PointLight light;
uniform DirectionalLight dirLight;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // === Directional light ===
    vec3 dirLightDir = normalize(-dirLight.direction); // direction opposée
    float diff1 = max(dot(norm, dirLightDir), 0.0);
    vec3 diffuse1 = diff1 * dirLight.color;

    vec3 reflectDir1 = reflect(-dirLightDir, norm);
    float spec1 = pow(max(dot(viewDir, reflectDir1), 0.0), 32);
    vec3 specular1 = 0.5 * spec1 * dirLight.color;

    vec3 ambient1 = 0.1 * dirLight.color;

    // === Point light ===
    vec3 lightDir = normalize(light.position - FragPos);
    float diff2 = max(dot(norm, lightDir), 0.0);
    vec3 diffuse2 = diff2 * light.color;

    vec3 reflectDir2 = reflect(-lightDir, norm);
    float spec2 = pow(max(dot(viewDir, reflectDir2), 0.0), 32);
    vec3 specular2 = 0.5 * spec2 * light.color;

    vec3 ambient2 = 0.1 * light.color;

    // === Résultat total ===

    vec3 texColor = objectColor;

    vec3 lighting = (ambient1 + diffuse1 + specular1) + (ambient2 + diffuse2 + specular2);
    if(useTexture)
        texColor = texture(texture_diffuse1, TexCoord).rgb;

    FragColor = vec4(10.0 * lighting * texColor, 1.0);
}


