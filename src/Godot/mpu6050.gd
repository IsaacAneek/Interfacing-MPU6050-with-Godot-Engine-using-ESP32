extends CSGBox3D

var server := UDPServer.new()

#	Change these according to your needs.
#	First start the program. The box will start with a weird angle. Note those
#	initial angles and put those here but with the opposite sign.
@export var angle_offset_x : float = -87.94221
@export var angle_offset_y : float = 66.22679
@export var angle_offset_z : float = 95.60239

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
		
		#	These act like sus change accordinly to your need
		x = angle_array["data"][1] + angle_offset_y + 180
		y = angle_array["data"][0] + angle_offset_x + 180
		z = - ( angle_array["data"][2] + angle_offset_z + 180 )
		
		#	Currently using euler angles to rotate things but this needs to be updated
		#	to use Quaternions instead
		var newRotation : Vector3 = Vector3(deg_to_rad(y), deg_to_rad(z) , deg_to_rad(x))
		
		rotation = newRotation
		
		# Reply so it knows we received the message.
		peer.put_packet(packet)
		# Keep a reference so we can keep contacting the remote peer.
		
