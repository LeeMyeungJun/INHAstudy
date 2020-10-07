#pragma once
class cPath
{

private:
	D3DXVECTOR3 m_vNode;
	D3DXVECTOR3* m_vPosition;
	D3DXVECTOR3* m_vDirection;
	cPath*		m_NextNode;
	
public:
	void Update();


public:
	D3DXVECTOR3* get_m_v_position() const
	{
		return m_vPosition;
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
	
	

	void set_m_next_node(cPath* m_next_node)
	{
		m_NextNode = m_next_node;
	}

	cPath* get_m_next_node() const
	{
		return m_NextNode;
	}

	

public:
	cPath();
	~cPath();
};

