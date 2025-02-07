extends CharacterBody2D
var server := UDPServer.new()

@export var angle_offset_x : float = 106.2792
@export var angle_offset_y : float = -219.8227
@export var angle_offset_z : float = -148.5253

@export var x : float
@export var y : float
@export var z : float




func _ready():
	server.listen(3333)

func _process(delta):
	server.poll() # Important!
	if server.is_connection_available():
		var peer: PacketPeerUDP = server.take_connection()
		var packet = peer.get_packet()
		var angleStringData = packet.get_string_from_utf8()
		print("Accepted peer: %s:%s" % [peer.get_packet_ip(), peer.get_packet_port()])
		print("Received data: %s" % angleStringData)
		
		var angle_array = JSON.parse_string(angleStringData)

		x = angle_array["data"][1] + angle_offset_y
		y = angle_array["data"][0] + angle_offset_x 
		z = angle_array["data"][2] + angle_offset_z
		
		var newRotation : Vector3 = Vector3(deg_to_rad(y), deg_to_rad(z) , deg_to_rad(x))
		
		# Reply so it knows we received the message.
		peer.put_packet(packet)
		# Keep a reference so we can keep contacting the remote peer.
		
