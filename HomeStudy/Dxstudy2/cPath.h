#pragma once
class cPath
{

private:
	D3DXVECTOR3 m_vNode;
	D3DXVECTOR3* m_vPosition;
	D3DXVECTOR3* m_vDirection;

	
public:
	void Update(D3DXMATRIXA16* matR);


public:
	D3DXVECTOR3 get_m_v_position() const
	{
		return *m_vPosition;
	}

	void set_m_v_position(D3DXVECTOR3* m_v_position)
	{
		m_vPosition = m_v_position;
	}

	
	D3DXVECTOR3 get_m_v_node() const
	{
		return m_vNode;
	}

	void set_m_v_node(const D3DXVECTOR3& m_v_node)
	{
		m_vNode = m_v_node;

		
	}
	D3DXVECTOR3* get_m_v_direction() const
	{
		return m_vDirection;
	}

	void set_m_v_direction(D3DXVECTOR3* m_v_direction)
	{
		m_vDirection = m_v_direction;
	}
	
	


	

public:
	cPath();
	~cPath();
};

