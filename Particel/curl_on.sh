## Particel.io Turn led ON
#curl https://api.particle.io/v1/devices/your-device-ID-goes-here/led -d access_token=your-access-token-goes-here -d arg=on

curl -d '{"arg":"on"}' -H "Content-Type: application/json" -X POST https://api.particle.io/v1/devices/your-device-ID-goes-here/led?access_token=your-access-token-goes-here

